#include "Fifo.h"

//namespace fifo {

Define_Module(Fifo);

void Fifo::initialize() {
    serviceTime = QUEUE_PROCESS_INTERVAL;
    isScheduled = false;

    energyQueue = cQueue("energyQueue", this->comparePriority);
    dequeueActionMsg = new cMessage("dequeueActionMsg");
    priorityMsgDequeueRequest = new cMessage("priorityMsgDequeueRequest");
    regularQueueCheckMsg = new cMessage("regularQueueCheckMsg");

    qlenSignal = registerSignal("queueLength");
    busySignal = registerSignal("busy");
    queueingTimeSignal = registerSignal("queueingTime");
    emit(qlenSignal, energyQueue.getLength());
    emit(busySignal, 0);
}

void Fifo::handleMessage(cMessage *msg) {
    // Case for dequeue action message
    if(msg == dequeueActionMsg) {
        dequeueMessage();
    }

    // Case for high priority message
    if(msg == priorityMsgDequeueRequest) {
        scheduleAt(simTime()+DEQUEUE_TRAFFIC_TIME, dequeueActionMsg);
        return;
    }

    // Case for regular queue check
    if(msg == regularQueueCheckMsg) {
        if(!energyQueue.isEmpty()) {
            dequeueMessage();
            scheduleAt(simTime()+DEQUEUE_TRAFFIC_TIME, regularQueueCheckMsg);
        } else {
            // Queue empty
            isScheduled = false;
            emit(busySignal, 0);
        }
        return;
    }

    // Case for energy message
    EnergyMsg *eMsg = check_and_cast<EnergyMsg*>(msg);
    if(eMsg) {
        eMsg->setEnqueueTimestamp(simTime());
        energyQueue.insert(eMsg);
        emit(qlenSignal, energyQueue.getLength());
    }

    // Dequeue periodically
    checkQueue(serviceTime);
}

void Fifo::checkQueue(simtime_t time) {
    // Regular Message Dequeue
    if(!isScheduled) {
        scheduleAt(simTime()+time, regularQueueCheckMsg);
        isScheduled = true;
        emit(busySignal, 1);
//        Traffic().trafficGenerator(time, priorityMsgDequeueRequest);
    }
}

simtime_t Fifo::startService(cMessage *msg)
{
    return simTime();
}

void Fifo::dequeueMessage()
{
    if(!energyQueue.isEmpty()) {
        cMessage* msg = check_and_cast<cMessage*>(energyQueue.pop());

        emit(qlenSignal, energyQueue.getLength());
        emit(queueingTimeSignal, simTime() - msg->getTimestamp());

        forwardMessage(msg);
    }

    EV << "Dequeue Energy Message at " << simTime() <<endl;
}

void Fifo::forwardMessage(cMessage* msg) {
    EnergyMsg *eMsg = check_and_cast<EnergyMsg*>(msg);
    int n = gateSize("in");
    int queueOutGateId = eMsg->getSource()%n;
    send(msg, "out", queueOutGateId);
    EV << "EnergyQueue forwarding message to MacroCell from out gate " << queueOutGateId << endl;
}

int Fifo::comparePriority(cObject* a, cObject* b) {
    EnergyMsg *aMsg = check_and_cast<EnergyMsg*>(a);
    EnergyMsg *bMsg = check_and_cast<EnergyMsg*>(b);

    return aMsg->getPriority() > bMsg->getPriority() ? 1 : -1;
}

//}; //namespace


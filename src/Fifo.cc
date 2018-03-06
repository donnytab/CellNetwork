#include "Fifo.h"

//namespace fifo {

Define_Module(Fifo);

void Fifo::initialize() {
    serviceTime = QUEUE_PROCESS_INTERVAL;
    isScheduled = false;
//    int queueMsgIndex = 0;

    energyQueue = cQueue("energyQueue", comparePriority);
    dequeueActionMsg = new cMessage("dequeueActionMsg");
    endServiceMsg = new cMessage("endServiceMsg");
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
    if(msg == endServiceMsg) {
        scheduleAt(simTime()+DEQUEUE_TRAFFIC_TIME, dequeueActionMsg);
        return;
    }

    // Case for regular queue check
    if(msg == regularQueueCheckMsg) {
        if(!energyQueue.isEmpty()) {
            dequeueMessage();
//            ++queueMsgIndex;
            scheduleAt(simTime()+DEQUEUE_TRAFFIC_TIME, regularQueueCheckMsg);
        } else {
            // Queue empty
            isScheduled = false;
//            queueMsgIndex = 0;
            emit(busySignal, 0);
        }
        return;

//        while(!energyQueue.isEmpty()) {
//            ++msgIndex;
//            scheduleAt(simTime()+DEQUEUE_TRAFFIC_TIME*msgIndex, dequeueActionMsg);
//        }
//        isScheduled = false;
//        emit(busySignal, 0);
//        return;
    }

    // Case for energy message
    EnergyMsg *eMsg = check_and_cast<EnergyMsg*>(msg);
    if(eMsg) {
        eMsg->setEnqueueTimestamp(simTime());
        energyQueue.insert(eMsg);
        emit(qlenSignal, energyQueue.getLength());
    }

    // Dequeue periodically
//    if(!isScheduled) {
//        scheduleAt(simTime()+serviceTime, endServiceMsg);
//        isScheduled = true;
//        emit(busySignal, 1);
//    }
    checkQueue(serviceTime);
}

void Fifo::checkQueue(simtime_t time) {
    // Regular Message Dequeue
    if(!isScheduled) {
        scheduleAt(simTime()+time, regularQueueCheckMsg);
        isScheduled = true;
        emit(busySignal, 1);
//        Traffic().trafficGenerator(time, endServiceMsg);
    }
}

simtime_t Fifo::startService(cMessage *msg)
{
//    EV << "Starting service of " << msg->getName() << endl;
    return simTime();
}

void Fifo::dequeueMessage()
{
    if(!energyQueue.isEmpty()) {
        cMessage* msg = check_and_cast<cMessage*>(energyQueue.pop());

        emit(qlenSignal, energyQueue.getLength());
        emit(queueingTimeSignal, simTime() - msg->getTimestamp());

        forwardMessage(msg);

        // TODO: traffic generator
//        checkQueue(DEQUEUE_TRAFFIC_TIME);
//        scheduleAt(simTime()+time, endServiceMsg);
    }
//    else {
//        isScheduled = false;
//        emit(busySignal, 0);
//    }

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

    return aMsg->getPriority() < bMsg->getPriority() ? 1 : -1;
}

//}; //namespace


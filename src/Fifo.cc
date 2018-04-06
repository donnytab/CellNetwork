#include "Fifo.h"

//namespace fifo {

Define_Module(Fifo);

void Fifo::initialize() {
    serviceTime = QUEUE_PROCESS_INTERVAL;
    isScheduled = false;
    totalPacket = 0;

    throughputStat.setName("Average throughput");

    energyQueue = cQueue("energyQueue", this->comparePriority);
    dequeueActionMsg = new cMessage("dequeueActionMsg");
    priorityMsgDequeueRequest = new cMessage("priorityMsgDequeueRequest");
    regularQueueCheckMsg = new cMessage("regularQueueCheckMsg");
    statRecordMsg = new cMessage("statRecordMsg");

    qlenSignal = registerSignal("queueLength");
    busySignal = registerSignal("busy");
    queueingTimeSignal = registerSignal("queueingTime");
    avgThroughputSignal = registerSignal("averageThroughput");

    emit(qlenSignal, energyQueue.getLength());
    emit(busySignal, 0);
    emit(avgThroughputSignal, 0);
    scheduleAt(simTime(), statRecordMsg);
}

void Fifo::handleMessage(cMessage *msg) {
    if(msg == statRecordMsg) {
        double currentThroughput = getAverageThroughput(totalPacket, simTime());
        throughputStat.collect(currentThroughput);
        if(energyQueue.getLength() != 0) {
            scheduleAt(simTime()+1.0, statRecordMsg);
        }
        return;
    }

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
        totalPacket++;
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

void Fifo::finish() {
    throughputStat.record();
}

double Fifo::getAverageThroughput(int packetNum, simtime_t time) {
    return time > 0 ? (double)packetNum*8/time : 0.0;    // bps
}

//}; //namespace


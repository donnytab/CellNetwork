#include "Fifo.h"

//namespace fifo {

Define_Module(Fifo);

void Fifo::initialize() {
    serviceTime = QUEUE_PROCESS_INTERVAL;
    isScheduled = false;
    energyQueue = cQueue("energyQueue", comparePriority);
    endServiceMsg = new cMessage("endServiceMsg");
}

void Fifo::handleMessage(cMessage *msg) {
    if(msg == endServiceMsg) {
        endService();
        return;
    }

    EnergyMsg *eMsg = check_and_cast<EnergyMsg*>(msg);
    if(eMsg) {
        energyQueue.insert(eMsg);
    }

    if(!isScheduled) {
        scheduleAt(simTime()+serviceTime, endServiceMsg);
        isScheduled = true;
    }
}

simtime_t Fifo::startService(cMessage *msg)
{
//    EV << "Starting service of " << msg->getName() << endl;
    return simTime();
}

void Fifo::endService()
{
//    EV << "Completed service of " << msg->getName() << endl;
//    send( msg, "out" );
    while(!energyQueue.isEmpty()) {
        cMessage* msg = check_and_cast<cMessage*>(energyQueue.pop());
        forwardMessage(msg);
    }
    isScheduled = false;

    EV << "End Service at " << simTime() <<endl;
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


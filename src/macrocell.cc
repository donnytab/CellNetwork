#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "energy_m.h"

using namespace omnetpp;

#define ENERGY_MESSAGE_TYPE "energyMessage"

class MacroCell : public cSimpleModule
{
private:
    cArray storeArray;
    int timeSensitiveCount;
    int timeMediumCount;
    int timeTolerantCount;
    simtime_t timeSensitiveTimeAverage;
    simtime_t timeMediumTimeAverage;
    simtime_t timeTolerantTimeAverage;
    simsignal_t msgTimeSignal;
    simsignal_t timeSensitiveQueueMsgTimeSignal;    // high priority, priority equals 0
    simsignal_t timeMediumQueueMsgTimeSignal;   // medium priority, priority equals 1
    simsignal_t timeTolerantQueueMsgTimeSignal; // low priority, priority equals 2
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    void processMessageTime(int priority, simtime_t time);
};

Define_Module(MacroCell);

void MacroCell::initialize()
{
    storeArray = cArray("engergyDataStore");
    msgTimeSignal = registerSignal("messageTime");
    timeSensitiveQueueMsgTimeSignal = registerSignal("timeSensitiveQueueMsgTime");
    timeMediumQueueMsgTimeSignal = registerSignal("timeMediumQueueMsgTime");
    timeTolerantQueueMsgTimeSignal = registerSignal("timeTolerantQueueMsgTime");
    timeSensitiveCount = 0;
    timeMediumCount = 0;
    timeTolerantCount = 0;
}

void MacroCell::handleMessage(cMessage *msg)
{
    if(!strcmp(msg->getName(), ENERGY_MESSAGE_TYPE)) {
        EnergyMsg *eMsg = check_and_cast<EnergyMsg*>(msg);
        eMsg->setEndTimestamp(simTime());
        processMessageTime(eMsg->getPriority(), simTime() - eMsg->getStartTimestamp());
//        emit(msgTimeSignal, simTime() - eMsg->getStartTimestamp());
        storeArray.add(check_and_cast<cObject*>(msg));
    }
}

void MacroCell::finish() {
    emit(timeSensitiveQueueMsgTimeSignal, (double)timeSensitiveTimeAverage.dbl()/timeSensitiveCount);
    emit(timeMediumQueueMsgTimeSignal, (double)timeMediumTimeAverage.dbl()/timeMediumCount);
    emit(timeTolerantQueueMsgTimeSignal, (double)timeTolerantTimeAverage.dbl()/timeTolerantCount);
}

void MacroCell::processMessageTime(int priority, simtime_t time) {
    switch(priority) {
        case 0:
            timeSensitiveTimeAverage += time;
            timeSensitiveCount++;
            break;
        case 1:
            timeMediumTimeAverage += time;
            timeMediumCount++;
            break;
        case 2:
            timeTolerantTimeAverage += time;
            timeTolerantCount++;
            break;
    }
}

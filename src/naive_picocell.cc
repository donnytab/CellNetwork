#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "energy_m.h"
#include "traffic.h"

using namespace omnetpp;
using namespace std;

class NaivePicoCell : public cSimpleModule
{
protected:
    virtual void forwardMessage(EnergyMsg *msg);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(NaivePicoCell);

void NaivePicoCell::initialize()
{
}

void NaivePicoCell::handleMessage(cMessage *msg)
{
    EnergyMsg *eMsg = check_and_cast<EnergyMsg*>(msg);
    if(eMsg) {
       forwardMessage(eMsg);
    }
}

void NaivePicoCell::forwardMessage(EnergyMsg *msg)
{
    sendDelayed(msg, NAIVE_MSG_FORWARD_TIME, "out", 0);
}

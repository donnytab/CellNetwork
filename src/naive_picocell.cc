#include "naive_picocell.h"

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

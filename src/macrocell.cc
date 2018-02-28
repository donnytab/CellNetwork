#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "energy_m.h"

using namespace omnetpp;

class MacroCell : public cSimpleModule
{
protected:
    virtual EnergyMsg *generateMessage();
    virtual void forwardMessage(EnergyMsg *msg);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(MacroCell);

void MacroCell::initialize()
{
}

void MacroCell::handleMessage(cMessage *msg)
{
    EnergyMsg *ttmsg = check_and_cast<EnergyMsg *>(msg);

    if (ttmsg->getDestination() == getIndex()) {
        // Message arrived.
        EV << "Message " << ttmsg << " arrived after " << ttmsg->getHopCount() << " hops.\n";
        bubble("ARRIVED, starting new one!");
        delete ttmsg;

        // Generate another one.
        EV << "Generating another message: ";
        EnergyMsg *newmsg = generateMessage();
        EV << newmsg << endl;
        forwardMessage(newmsg);
    }
    else {
        // We need to forward the message.
//        forwardMessage(ttmsg);
    }
}

EnergyMsg *MacroCell::generateMessage()
{
    int src = getIndex();
    int n = getVectorSize();
    int dest = intuniform(0, n-2);
    if(dest >= src)
        dest++;

    char msgname[20];
    sprintf(msgname, "tic-%d-to-%d", src, dest);

    EnergyMsg *msg = new EnergyMsg(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

void MacroCell::forwardMessage(EnergyMsg *msg)
{
    // Increment hop count.
    msg->setHopCount(msg->getHopCount()+1);

    // Same routing as before: random gate.
    int n = gateSize("gate");
    int k = intuniform(0, n-1);

    EV << "Forwarding message " << msg << " on gate[" << k << "]\n";
    send(msg, "gate$o", k);
}

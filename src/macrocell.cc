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
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(MacroCell);

void MacroCell::initialize()
{
    storeArray = cArray("engergyDataStore");
}

void MacroCell::handleMessage(cMessage *msg)
{
    if(!strcmp(msg->getName(), ENERGY_MESSAGE_TYPE)) {
        storeArray.add(check_and_cast<cObject*>(msg));
    }
}

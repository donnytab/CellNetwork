#ifndef SRC_NAIVE_PICOCELL_H_
#define SRC_NAIVE_PICOCELL_H_

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

    simsignal_t avgThroughputSignal;
};



#endif /* SRC_NAIVE_PICOCELL_H_ */

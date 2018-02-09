#include <stdio.h>
#include <queue>
#include <mutex>
#include <memory>
#include <string.h>
#include <omnetpp.h>
#include "energy_m.h"

using namespace omnetpp;
using namespace std;

class MsgCompare {
public:
    bool operator() (const EnergyMsg* eMsg1, const EnergyMsg* eMsg2) const
    {
        if(eMsg1->getPriority() < eMsg2->getPriority()) {
            return (eMsg1 > eMsg2);
        }
    }
};

class PicoCell : public cSimpleModule
{
private:
    priority_queue<EnergyMsg*, vector<EnergyMsg*>, MsgCompare> energyQueue;
    mutex mtx;
    condition_variable conVar;
  protected:
//    virtual EnergyMsg *generateMessage();
    virtual void forwardMessage(EnergyMsg *msg);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(PicoCell);

void PicoCell::initialize()
{
}

void PicoCell::handleMessage(cMessage *msg)
{
    EnergyMsg *eMsg = check_and_cast<EnergyMsg*>(msg);

    eMsg->setPriority(eMsg->getSource());

    unique_lock<mutex> lck(mtx);
    if(eMsg) {
        energyQueue.push(eMsg);
        bubble("PUSH!");
        conVar.notify_one();
    }

    while(!energyQueue.empty()) {
        forwardMessage(energyQueue.top());
        energyQueue.pop();
    }
}

void PicoCell::forwardMessage(EnergyMsg *msg)
{
//    // Increment hop count.
//    msg->setHopCount(msg->getHopCount()+1);

    // Same routing as before: random gate.
    int n = gateSize("gate");
    int k = intuniform(0, n-1);

    EV << "Forwarding message " << msg << " on gate[" << k << "]\n";
    send(msg, "gate$o", 0);
}


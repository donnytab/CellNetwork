#ifndef __FIFO_H
#define __FIFO_H

#include <omnetpp.h>
#include "energy_m.h"

using namespace omnetpp;

#define QUEUE_PROCESS_INTERVAL 5.0;

//namespace fifo {

/**
 * Single-server queue with a given service time.
 */
class Fifo : public cSimpleModule
{
  public:
//    Fifo();
//    ~Fifo();
    static int comparePriority(cObject* a, cObject* b);

  protected:
    cMessage *msgServiced;
    cMessage *endServiceMsg;    // self-message for processing delay
//    cQueue queue;
    cQueue energyQueue;

    simtime_t serviceTime;
    simsignal_t qlenSignal;
    simsignal_t busySignal;
    simsignal_t queueingTimeSignal;

    bool isScheduled;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void forwardMessage(cMessage *msg);
    virtual simtime_t startService(cMessage *msg);
    virtual void endService();
};

//}; //namespace

#endif

#ifndef __FIFO_H
#define __FIFO_H

#include <omnetpp.h>
#include "energy_m.h"
#include "traffic.h"

using namespace omnetpp;
using namespace std;

#define QUEUE_PROCESS_INTERVAL 1.0;
#define STAT_RECORD_INTERVAL 1.0;

//namespace fifo {

/**
 * Single-server queue with a given service time.
 */
class Fifo : public cSimpleModule
{
  public:
    static int comparePriority(cObject* a, cObject* b);

  protected:
    cMessage *dequeueActionMsg;
    cMessage *priorityMsgDequeueRequest;    // self-message for processing high priority messsage
    cMessage *regularQueueCheckMsg;
    cMessage* statRecordMsg;
    cQueue energyQueue;

    simtime_t serviceTime;
    simsignal_t qlenSignal;
    simsignal_t busySignal;
    simsignal_t queueingTimeSignal;
    simsignal_t avgThroughputSignal;

    cStdDev throughputStat;

    bool isScheduled;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void forwardMessage(cMessage *msg);
    virtual void checkQueue(simtime_t time);
    virtual simtime_t startService(cMessage *msg);
    virtual void dequeueMessage();
    virtual void finish();
    double getAverageThroughput(int packetNum, simtime_t time);

  private:
    int totalPacket;
};

//}; //namespace

#endif

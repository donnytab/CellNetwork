#ifndef SRC_TRAFFIC_H_
#define SRC_TRAFFIC_H_

/*
 * Definitions for different types of traffic time
 */
#define DEQUEUE_TRAFFIC_TIME 0.2
#define ENQUEUE_TRAFFIC_TIME 0.2

#include <omnetpp.h>

using namespace omnetpp;

class Traffic : public cSimpleModule {
public:
    Traffic(){}
    void trafficGenerator(simtime_t trafficTime, cMessage* msg);
};

//void Traffic::trafficGenerator(simtime_t trafficTime, cMessage* msg) {
//    scheduleAt(simTime()+trafficTime, msg);
//}

#endif /* SRC_TRAFFIC_H_ */

#ifndef SRC_TRAFFIC_H_
#define SRC_TRAFFIC_H_

/*
 * Definitions for different types of traffic time
 */
#define DEQUEUE_TRAFFIC_TIME 1
#define ENQUEUE_TRAFFIC_TIME 1

#include <omnetpp.h>

using namespace omnetpp;

static class Traffic {
public:
    void trafficGenerator(simtime_t trafficTime);
};

#endif /* SRC_TRAFFIC_H_ */

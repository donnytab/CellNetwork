#ifndef SRC_NAIVE_PICOCELL_H_
#define SRC_NAIVE_PICOCELL_H_

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "energy_m.h"
#include "traffic.h"

#include <queue>
#include <mutex>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <omnetpp.h>
#include "kmeans.h"
#include "priority_m.h"

using namespace omnetpp;
using namespace std;

#define PRIORITY_LEVEL 3    // K value for Kmeans algorithm
#define TRAINING_SAMPLE_COUNT 50
#define MATRIX_COLUMN 1440      // Granularity for each training sample
#define ENERGYMATRIX_COLUMN 60      // Granularity for each chunk
#define PICOCELL_GATE_TOTAL 26    // 25 users + 1 macrocell
#define PRIORITY_UPDATE_INTERVAL 1.0

class NaivePicoCell : public cSimpleModule
{
private:
//    priority_queue<EnergyMsg*, vector<EnergyMsg*>, MsgCompare> energyQueue;
    cQueue energyQueue;
    cMessage* updatePriorityMsg;
//    bool hasUpdatedPriority;
    int hasUpdatedPriority;
    double** trainingMatrix;
    double* modelCentroids;
    mutex mtx;
    condition_variable conVar;
    Kmeans kmeans;
protected:
//    virtual EnergyMsg *generateMessage();
    virtual void forwardEnergyMessage(EnergyMsg* eMsg);
    virtual void forwardPriorityMessage(PriorityMsg *pMsg);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void loadData();
    void trainModel();
    int evaluatePriority(EnergyMsg *msg);

    simsignal_t avgThroughputSignal;
};



#endif /* SRC_NAIVE_PICOCELL_H_ */

#include <stdio.h>
#include <queue>
#include <mutex>
#include <memory>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <omnetpp.h>
#include "kmeans.h"
#include "energy_m.h"
#include "priority_m.h"

using namespace omnetpp;
using namespace std;

#define PRIORITY_LEVEL 3    // K value for Kmeans algorithm
#define TRAINING_SAMPLE_COUNT 50
#define MATRIX_COLUMN 1440      // Granularity for each training sample
#define ENERGYMATRIX_COLUMN 60      // Granularity for each chunk
#define PICOCELL_GATE_TOTAL 26    // 25 users + 1 macrocell
#define PRIORITY_UPDATE_INTERVAL 1.0

class MsgCompare {
public:
    bool operator() (const EnergyMsg* eMsg1, const EnergyMsg* eMsg2) const
    {
        if(eMsg1->getPriority() < eMsg2->getPriority()) {
            return (eMsg1 > eMsg2);
        }
    }
};

class PicoSink : public cSimpleModule
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
};

Define_Module(PicoSink);

void PicoSink::initialize()
{
//    energyQueue = cQueue("energyQueue", comparePriority);
    updatePriorityMsg = new cMessage("updatePriorityMsg");
//    hasUpdatedPriority = false;     // false: to update priority
    hasUpdatedPriority = 0;     // 0: to update priority
    kmeans = Kmeans();
    trainingMatrix = new double* [TRAINING_SAMPLE_COUNT];
    for(int i=0; i<TRAINING_SAMPLE_COUNT; i++) {
        trainingMatrix[i] = new double [MATRIX_COLUMN];
    }
    modelCentroids = new double [PRIORITY_LEVEL];
    loadData();
    trainModel();
    for(int j=0; j<PRIORITY_LEVEL; j++) {
        EV << "picocell "+ to_string(getIndex()) +" priority "+ to_string(j) + " : " + to_string(modelCentroids[j])<<endl;
    }
}

void PicoSink::handleMessage(cMessage *msg)
{
    unique_lock<mutex> lck(mtx);
    int priority = -1;
    EnergyMsg *eMsg;

    if(msg == updatePriorityMsg) {
        hasUpdatedPriority = 0;
        return;
    }

    if(!strcmp(msg->getName(), "energyMessage")) {
        eMsg = check_and_cast<EnergyMsg*>(msg);
    }

    if(hasUpdatedPriority<PRIORITY_LEVEL && eMsg) {
        // Create priority message
        PriorityMsg *pMsg = new PriorityMsg();
        priority = evaluatePriority(eMsg);
        pMsg->setName("priorityMessage");
        pMsg->setSource(getIndex());
        pMsg->setDestination(eMsg->getSource());
//        EV << "GET sink INDEX: " << eMsg->getSource() <<endl;
        if(priority >= 0) {
            pMsg->setPriority(priority);
        }

        // Forward priority back to users
        forwardPriorityMessage(pMsg);

//        hasUpdatedPriority = true;
        hasUpdatedPriority++;

        if(!updatePriorityMsg->isScheduled()) {
            scheduleAt(simTime()+PRIORITY_UPDATE_INTERVAL, updatePriorityMsg);
        }
    }

    // Set priority of the current energy message before forwarding
    eMsg->setPreviousEventNumber(priority);
    forwardEnergyMessage(eMsg);

    conVar.notify_one();
}

void PicoSink::forwardEnergyMessage(EnergyMsg* eMsg)
{
    cMessage* msg = check_and_cast<cMessage*>(eMsg);
    int n = gateSize("in");
    int sinkOutGateId = eMsg->getSource()%n;
    send(msg, "out", sinkOutGateId);
    EV << "Forwarding picosink Energy message " << msg << " to Macrocell\n";
}

void PicoSink::forwardPriorityMessage(PriorityMsg *pMsg)
{
//    int userGateId = (pMsg->getDestination())%PICOCELL_GATE_TOTAL;
    int n = gateSize("priorityOut");
    int userGateId = (pMsg->getDestination())%n;
    send(pMsg, "priorityOut", userGateId);
    EV << "Forwarding " << userGateId<< " priority message" << pMsg << " on gate[" << userGateId <<"]\n";
}

void PicoSink::loadData() {
    string row;
    char delimeter = ',';
    string datasetDir = "/Users/downson/omnetpp-5.2/samples/CellNetwork/res/trainingset";
    for(int i=0; i<TRAINING_SAMPLE_COUNT; i++) {
        int index = 0;
        string fileDir = datasetDir + string("/t-") + to_string(i) + string(".csv");
        ifstream infile(fileDir);
        if(!infile) {
            exit(1);
        }
        while(getline(infile, row)) {
            stringstream s(row);
            string item;
            getline(s, item, delimeter);    // Remove timestamp
            getline(s, item, delimeter);
            trainingMatrix[i][index] = atof(item.c_str());
            index++;
        }
        infile.close();
    }
}

void PicoSink::trainModel() {
    modelCentroids = kmeans.generateKmeansClusters(trainingMatrix, PRIORITY_LEVEL);
    sort(modelCentroids, modelCentroids+PRIORITY_LEVEL);
}

int PicoSink::evaluatePriority(EnergyMsg *msg) {
    double rms, sum = 0;
    double minDiff = SHORTEST_MAX;
    int priority;

    // Get delta value & Calculate root mean square
    for(int i=0; i<ENERGYMATRIX_COLUMN-1; i++) {
        double delta = msg->getEnergyCost(i+1) - msg->getEnergyCost(i);
        sum += delta * delta;
    }

    rms = sqrt(sum);

    for(int j=0; j<PRIORITY_LEVEL; j++) {
        if(abs(rms - modelCentroids[j]) < minDiff) {
            minDiff = abs(rms - modelCentroids[j]);
            priority = j;
        }
    }

    return priority;
}

//int PicoSink::comparePriority(cObject* a, cObject* b) {
//    EnergyMsg *aMsg = check_and_cast<EnergyMsg*>(a);
//    EnergyMsg *bMsg = check_and_cast<EnergyMsg*>(b);
//
//    return aMsg->getPriority() < bMsg->getPriority() ? 1 : -1;
//}

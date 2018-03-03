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
    double** trainingMatrix;
    double* modelCentroids;
    mutex mtx;
    condition_variable conVar;
    Kmeans kmeans;
protected:
//    virtual EnergyMsg *generateMessage();
    virtual void forwardMessage(EnergyMsg *msg);
    virtual void forwardPriorityMessage(PriorityMsg *pMsg);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void loadData();
    void trainModel();
    int evaluatePriority(EnergyMsg *msg);
public:
    static int comparePriority(cObject* a, cObject* b);
};

Define_Module(PicoSink);

void PicoSink::initialize()
{
    energyQueue = cQueue("energyQueue", comparePriority);
    kmeans = Kmeans();
    trainingMatrix = new double* [TRAINING_SAMPLE_COUNT];
    for(int i=0; i<TRAINING_SAMPLE_COUNT; i++) {
        trainingMatrix[i] = new double [MATRIX_COLUMN];
    }
    modelCentroids = new double [PRIORITY_LEVEL];
    loadData();
    trainModel();
}

void PicoSink::handleMessage(cMessage *msg)
{
    EnergyMsg *eMsg = check_and_cast<EnergyMsg*>(msg);
    PriorityMsg *pMsg = new PriorityMsg();

    unique_lock<mutex> lck(mtx);
    if(eMsg) {
        pMsg->setSource(getIndex());
        pMsg->setDestination(eMsg->getSource());
        pMsg->setPriority(evaluatePriority(eMsg));
//        bubble(to_string(evaluatePriority(eMsg)).c_str());

        energyQueue.insert(eMsg);

//        bubble("PUSH!");
        ostringstream s;
        s << modelCentroids[2];
        bubble(s.str().c_str());

        conVar.notify_one();
    }
    // CBR, VBR, RT-VBR

    while(!energyQueue.isEmpty()) {
        forwardMessage((EnergyMsg*)energyQueue.pop());
    }

//    if(eMsg->getPriority() == -1) {
//        forwardPriorityMessage(pMsg);
//    }
}

void PicoSink::forwardMessage(EnergyMsg *msg)
{
    int n = gateSize("in");
    int sinkOutGateId = msg->getSource()%n;
    send(msg, "out", sinkOutGateId);
    EV << "Forwarding Energy message " << msg << " to Macrocell\n";
}

void PicoSink::forwardPriorityMessage(PriorityMsg *pMsg)
{
    int userGateId = (pMsg->getDestination())%PICOCELL_GATE_TOTAL;
    send(pMsg, "gate$o", userGateId);
    EV << "Forwarding priority message" << pMsg << " on gate[" << userGateId <<"]\n";
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
            while(getline(s, item, delimeter)) {
                trainingMatrix[i][index] = atof(item.c_str());
            }
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

int PicoSink::comparePriority(cObject* a, cObject* b) {
    EnergyMsg *aMsg = check_and_cast<EnergyMsg*>(a);
    EnergyMsg *bMsg = check_and_cast<EnergyMsg*>(b);

    return aMsg->getPriority() < bMsg->getPriority() ? 1 : -1;
}

#include <stdio.h>
#include <queue>
#include <mutex>
#include <memory>
#include <string.h>
#include <fstream>
#include <iostream>
#include <omnetpp.h>
#include "kmeans.h"
#include "energy_m.h"

using namespace omnetpp;
using namespace std;

#define PRIORITY_LEVEL 3    // K value for Kmeans algorithm
#define TRAINING_SAMPLE_COUNT 50
#define MATRIX_COLUMN 1440      // Granularity for each training sample

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
    double** trainingMatrix;
    double* modelCentroids;
    mutex mtx;
    condition_variable conVar;
    Kmeans kmeans;
  protected:
//    virtual EnergyMsg *generateMessage();
    virtual void forwardMessage(EnergyMsg *msg);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void loadData();
    void trainModel();
};

Define_Module(PicoCell);

void PicoCell::initialize()
{
    kmeans = Kmeans();
    trainingMatrix = new double* [TRAINING_SAMPLE_COUNT];
    for(int i=0; i<TRAINING_SAMPLE_COUNT; i++) {
        trainingMatrix[i] = new double [MATRIX_COLUMN];
    }
    modelCentroids = new double [PRIORITY_LEVEL];
    loadData();
    trainModel();
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

void PicoCell::loadData() {
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

void PicoCell::trainModel() {
    modelCentroids = kmeans.generateKmeansClusters(trainingMatrix, PRIORITY_LEVEL);
}

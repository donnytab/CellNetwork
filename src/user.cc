#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omnetpp.h>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include "energy_m.h"

using namespace omnetpp;
using namespace std;

#define MINUTE_MILLISECOND 60000
#define ENERGYMATRIX_ROW 24     // Number of message chunks
#define ENERGYMATRIX_COLUMN 60      // Granularity for each chunk

class User : public cSimpleModule
{
private:
    static double** energyMatrix;
protected:
//    virtual EnergyMsg* generateMessage();
    virtual void generateMessage();
    virtual void forwardMessage(EnergyMsg *msg);
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void loadDataset();
};

Define_Module(User);

double** User::energyMatrix;

void User::initialize()
{
    energyMatrix = new double* [24];
    for(int i=0; i<24; i++) {
        energyMatrix[i] = new double [60];
    }

    // Read energy data from dataset
    loadDataset();

    generateMessage();

//    EnergyMsg *msg = generateMessage();
//    scheduleAt(0.0, msg);
}

void User::handleMessage(cMessage *msg)
{
//        sleep(MINUTE_MILLISECOND);
        EnergyMsg *ttmsg = check_and_cast<EnergyMsg *>(msg);

        if (ttmsg->getDestination() == getIndex()) {
            // Message arrived.
            EV << "Message " << ttmsg << " arrived after " << ttmsg->getHopCount() << " hops.\n";
            bubble("ARRIVED, starting new one!");
            delete ttmsg;

            // Generate another one.
            EV << "Generating another message: ";
//            EnergyMsg *newmsg = generateMessage();
//            EV << newmsg << endl;
//            forwardMessage(newmsg);
        }
        else {
            // We need to forward the message.
            forwardMessage(ttmsg);
        }
}

//EnergyMsg *User::generateMessage()
void User::generateMessage()
{
    for(int i=0; i<ENERGYMATRIX_ROW; i++) {
        char msgname[30];
        int src = getIndex();
        int dest = intuniform(0, getVectorSize()-2);
        sprintf(msgname, "user %d to picocell %d", src, dest);
        EnergyMsg *msg = new EnergyMsg(msgname);
        for(int j=0; j<ENERGYMATRIX_COLUMN; j++) {
            msg->setEnergyCost(j, energyMatrix[i][j]);
        }
        msg->setSource(src);
        msg->setDestination(dest);
        scheduleAt(0.0+i*0.5, msg);
    }
}

void User::forwardMessage(EnergyMsg *msg)
{
    // Increment hop count.
    msg->setHopCount(msg->getHopCount()+1);

    // Same routing as before: random gate.
    int n = gateSize("gate");
    int k = intuniform(0, n-1);

    EV << "Forwarding message " << msg << " on gate[" << k << "]\n";
    send(msg, "gate$o", k);
}

void User::loadDataset() {
    string row;
    int index = 0;
    char delimeter = ',';
    string datasetDir = "/Users/downson/omnetpp-5.2/samples/CellNetwork/res/dataset";
    string fileDir = datasetDir + string("/") + to_string(getIndex()) + string(".csv");
    ifstream infile(fileDir);
    if(!infile) {
        exit(1);
    }
    while(getline(infile, row)) {
        stringstream s(row);
        string item;
        while(getline(s, item, delimeter)) {
            energyMatrix[index/60][index%60] = atof(item.c_str());
        }
        index++;
    }
    infile.close();
}

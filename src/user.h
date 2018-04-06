#ifndef SRC_USER_H_
#define SRC_USER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omnetpp.h>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include "energy_m.h"
#include "priority_m.h"

using namespace omnetpp;
using namespace std;

#define MINUTE_MILLISECOND 60000
#define ENERGYMATRIX_ROW 24     // Number of message chunks
#define ENERGYMATRIX_COLUMN 60      // Granularity for each chunk

class User : public cSimpleModule
{
private:
    static double** energyMatrix;
    static string** timestampMatrix;
    int priority;
    const char* ENERGY_MESSAGE_TYPE;
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
string** User::timestampMatrix;




#endif /* SRC_USER_H_ */

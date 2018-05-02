#include "user.h"

void User::initialize()
{
    priority = -1;
    ENERGY_MESSAGE_TYPE = "energyMessage";
    energyMatrix = new double* [24];
    for(int i=0; i<24; i++) {
        energyMatrix[i] = new double [60];
    }

    timestampMatrix = new string* [ENERGYMATRIX_ROW];
    for(int j=0; j<ENERGYMATRIX_ROW; j++) {
        timestampMatrix[j] = new string [ENERGYMATRIX_COLUMN];
    }

    // Read energy data from dataset
    loadDataset();

    generateMessage();
}

void User::handleMessage(cMessage *msg)
{
    if(!strcmp(msg->getName(), "energyMessage")) {
        forwardMessage(check_and_cast<EnergyMsg *>(msg));
    }

    if(!strcmp(msg->getName(), "priorityMessage")) {
        PriorityMsg* pMsg = check_and_cast<PriorityMsg*>(msg);
        priority = pMsg->getPriority();
    }
}

void User::generateMessage()
{
    for(int i=0; i<ENERGYMATRIX_ROW; i++) {
        int src = getIndex();
        int dest = intuniform(0, getVectorSize()-2);    // TODO
        EnergyMsg *msg = new EnergyMsg("energyMessage");
        for(int j=0; j<ENERGYMATRIX_COLUMN; j++) {
            msg->setEnergyCost(j, energyMatrix[i][j]);
        }
        for(int k=0; k<ENERGYMATRIX_COLUMN; k++) {
            msg->setTimestamp(k, timestampMatrix[i][k].c_str());
        }

        msg->setName(ENERGY_MESSAGE_TYPE);
        msg->setSource(src);
        msg->setDestination(dest);
        msg->setStartTimestamp(simTime());
        msg->setEnqueueTimestamp(0);
        msg->setDequeueTimestamp(0);
        scheduleAt(0.0+i*0.5, msg);
    }
}

void User::forwardMessage(EnergyMsg *msg)
{
    // Increment hop count.
    msg->setHopCount(msg->getHopCount()+1);

    EV << "Forwarding user message " << msg << " on gate[" << 0 << "]\n";
    send(msg, "out");
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

        // Get timestamp
        getline(s, item, delimeter);
        timestampMatrix[index/60][index%60] = item;

        // Get energy consumption data
        getline(s, item, delimeter);
        energyMatrix[index/60][index%60] = atof(item.c_str());

        index++;
    }
    infile.close();
}

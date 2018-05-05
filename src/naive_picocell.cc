#include "naive_picocell.h"

Define_Module(NaivePicoCell);

void NaivePicoCell::initialize()
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

void NaivePicoCell::handleMessage(cMessage *msg)
{
//    EnergyMsg *eMsg = check_and_cast<EnergyMsg*>(msg);
//    if(eMsg) {
//       forwardMessage(eMsg);
//    }
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

    //    if(hasUpdatedPriority<PRIORITY_LEVEL && eMsg) {
        if(eMsg) {
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
        eMsg->setPriority(priority);
        forwardEnergyMessage(eMsg);

        conVar.notify_one();
}

void NaivePicoCell::forwardEnergyMessage(EnergyMsg* eMsg)
{
    cMessage* msg = check_and_cast<cMessage*>(eMsg);
    int n = gateSize("in");
    int sinkOutGateId = eMsg->getSource()%n;
    send(msg, "out", sinkOutGateId);
    EV << "Forwarding picosink Energy message " << msg << " to Macrocell\n";
}

void NaivePicoCell::forwardPriorityMessage(PriorityMsg *pMsg)
{
//    int userGateId = (pMsg->getDestination())%PICOCELL_GATE_TOTAL;
    int n = gateSize("priorityOut");
    int userGateId = (pMsg->getDestination())%n;
    send(pMsg, "priorityOut", userGateId);
    EV << "Forwarding " << userGateId<< " priority message" << pMsg << " on gate[" << userGateId <<"]\n";
}

void NaivePicoCell::loadData() {
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

void NaivePicoCell::trainModel() {
    modelCentroids = kmeans.generateKmeansClusters(trainingMatrix, PRIORITY_LEVEL);
    sort(modelCentroids, modelCentroids+PRIORITY_LEVEL);
    reverse(modelCentroids, modelCentroids+PRIORITY_LEVEL);
}

int NaivePicoCell::evaluatePriority(EnergyMsg *msg) {
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

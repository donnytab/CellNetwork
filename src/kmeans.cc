#include "kmeans.h"

Kmeans::Kmeans() {
    deltaMatrix = new double* [DELTA_MATRIX_ROW];
    for(int i=0; i<DELTA_MATRIX_ROW; i++) {
        deltaMatrix[i] = new double [DELTA_MATRIX_COLUMN];
    }

    // Initialization
    for(int i=0; i<DELTA_MATRIX_ROW; i++) {
        for(int j=0; j<DELTA_MATRIX_COLUMN; j++) {
            deltaMatrix[i][j] = 0;
        }
    }
}

void Kmeans::loadData(double** energyData) {
    for(int i=0; i<DELTA_MATRIX_ROW; i++) {
        for(int j=0; j<DELTA_MATRIX_COLUMN; j++) {
            deltaMatrix[i][j] = fabs(energyData[i][j+1] - energyData[i][j]);
        }
    }
}

/*
 * @param dimension  size of array m.
 *
 */
double Kmeans::calculateDistance(double m[], double n[], int dimension) {
    double squareSum = 0;
    for(int i=0; i<dimension; i++) {
        double diff = m[i] - n[i];
        squareSum += diff * diff;
    }
    return sqrt(squareSum);
}

double** Kmeans::generateCentroids(int k) {
    double** centroids = new double* [k];
    for(int i=0; i<k; i++) {
        centroids[i] = new double [DELTA_MATRIX_COLUMN];
    }

    // Choose the max & min values for each column
    for(int i=0; i<DELTA_MATRIX_COLUMN; i++) {
        double max = 0;
        double min = 0;
        for(int j=0; j<DELTA_MATRIX_ROW; j++) {
            max = deltaMatrix[j][i] > max ? deltaMatrix[j][i] : max;
            min = deltaMatrix[j][i] < min ? deltaMatrix[j][i] : min;
        }

        // Generate random value between max & min
        for(int RandIndex=0; RandIndex<k; RandIndex++) {
            centroids[RandIndex][i] = rand() % ((int)(max-min+1)) + min;
        }
    }
    return centroids;
}

int* Kmeans::joinGroup(double** centroids, int k) {
    int* centroidIndexGroups = new int [DELTA_MATRIX_ROW];
    for(int i=0; i<DELTA_MATRIX_ROW; i++) {
        double shortest = SHORTEST_MAX;
        int shortest_index = 0;
        for(int j=0; j<k; j++) {
            double dist = calculateDistance(deltaMatrix[i], centroids[j], DELTA_MATRIX_COLUMN);

            // Find the closest centroid for each chunk
            if(dist < shortest) {
                shortest = dist;
                shortest_index = j;
            }
        }
        centroidIndexGroups[i] = shortest_index;
    }
    return centroidIndexGroups;
}

/*
 * @param dimension  size of array centroidIndexGroup[].
 *
 */
double** Kmeans::updateCentroids(int* centroidIndexGroup, int k) {
//    int num = sizeof(centroidIndexGroup)/sizeof(centroidIndexGroup[0]);
    int* groupDataCount = new int [k];
    double** newCentroids = new double* [k];

    for(int i =0; i<k; i++) {
        newCentroids[i] = new double [DELTA_MATRIX_COLUMN];
        groupDataCount[i] = 0;
    }

    // Initialization
    for(int i=0; i<k; i++) {
        for(int j=0; j<DELTA_MATRIX_COLUMN; j++) {
            newCentroids[i][j] = 0;
        }
    }

    // Calculate new centroids
    for(int i=0; i<DELTA_MATRIX_ROW; i++) {
        int groupIndex = centroidIndexGroup[i];
        for(int j=0; j<DELTA_MATRIX_COLUMN; j++) {
            newCentroids[groupIndex][j] += deltaMatrix[i][j];
        }
        groupDataCount[groupIndex] += 1;
    }

    // Calculate the average values of the new centroid
    for(int i=0; i<k; i++) {
        EV << "DATA GROUP count : " + to_string(groupDataCount[i]) <<endl;
        for(int j=0; j<DELTA_MATRIX_COLUMN; j++) {
            newCentroids[i][j] = (double)newCentroids[i][j]/groupDataCount[i];
        }
    }
    return newCentroids;
}

double* Kmeans::generateKmeansClusters(double** energyData, int k) {
    double** centroid = new double* [k];
    for(int i=0; i<k; i++) {
        centroid[i] = new double [DELTA_MATRIX_COLUMN];
    }

    int* group = new int [DELTA_MATRIX_ROW];
    int* prevGroup = new int [DELTA_MATRIX_ROW];

    // Group randomized initialization
    for(int i=0; i<DELTA_MATRIX_ROW; i++) {
        group[i] = 0;
        prevGroup[i] = rand()%k;
    }

    loadData(energyData);
    group = joinGroup(generateCentroids(k), k);

    // Generate clusters until the group indexes remain stable
    do {
        EV << "Clustering!!" <<endl;
        centroid = updateCentroids(group ,k);
        prevGroup = group;
        group = joinGroup(centroid, k);
    } while(!isEqual(group, prevGroup, DELTA_MATRIX_ROW));

    return getRootMeanSquare(centroid, k);
}

bool Kmeans::isEqual(int* group1, int* group2, int size) {
    for(int i=0; i<size; i++) {
        if(group1[i] != group2[i]) {
            return false;
        }
    }
    return true;
}

double* Kmeans::getRootMeanSquare(double** centroids, int k) {
    double* rootMeanSquare = new double [k];
    for(int i=0; i<k; i++) {
        double sum = 0;
        for(int j=0; j<DELTA_MATRIX_COLUMN; j++) {
            sum += centroids[i][j] * centroids[i][j];
        }

        EV << "SUM : " + to_string(sum) <<endl;

        rootMeanSquare[i] = sqrt(sum);
    }
    return rootMeanSquare;
}

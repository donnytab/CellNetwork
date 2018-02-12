#include <math.h>
#include <cstdlib>
#include <limits>

using namespace std;

#define DELTA_MATRIX_ROW 24     // Number of message chunks
#define DELTA_MATRIX_COLUMN 60      // Granularity for each chunk
#define SHORTEST_MAX numeric_limits<double>::max()

class Kmeans {
private:
    double** deltaMatrix;   // Two dimensional array for delta cost
protected:
    Kmeans();
    void loadData(double energyData[][]);
    double calculateDistance(double array1[], double array2[]) const;
    double** generateCentroids(int k);
    double* joinGroup(double centroids[][]);
    double* calculateCenterPoint(double** pointSet[][]);
    double** updateCentroids(double centroidIndexGroup[], int k);
};

Kmeans::Kmeans() {
    deltaMatrix = new double* [DELTA_MATRIX_ROW];
    for(int i=0; i<DELTA_MATRIX_ROW; i++) {
        deltaMatrix[i] = new double [DELTA_MATRIX_COLUMN];
    }
}

void Kmeans::loadData(double energyData[][]) {

}

double Kmeans::calculateDistance(double m[], double n[]) const {
    double squareSum = 0;
    int dimension = sizeof(m)/sizeof(m[0]);
    for(int i=0; i<dimension; i++) {
        double diff = m[i] - n[i];
        squareSum += diff * diff;
    }
    return sqrt(squareSum);
}

double** Kmeans::generateCentroid(int k) {
    int RandIndex = 0;
    double** centroids = new double* [k];
    for(int i=0; i<k; i++) {
        centroids[i] = new double [DELTA_MATRIX_COLUMN];
    }
    for(int i=0; i<DELTA_MATRIX_COLUMN; i++) {
        double max = 0;
        double min = 0;
        for(int j=0; j<DELTA_MATRIX_ROW; j++) {
            max = deltaMatrix[i][j] > max ? deltaMatrix[i][j] : max;
            min = deltaMatrix[i][j] < min ? deltaMatrix[i][j] : min;
        }
        centroids[RandIndex++][i] = rand() % (max-min+1) + min;
    }
    return centroids;
}

double* Kmeans::joinGroup(double centroids[][], int k) {
    double* centroidIndexGroups = new double[DELTA_MATRIX_ROW];
    for(int i=0; i<DELTA_MATRIX_ROW; i++) {
        double shortest = SHORTEST_MAX;
        int shortest_index = 0;
        for(int j=0; j<k; j++) {
            double dist = calculateDistance(deltaMatrix[i], centroids[j]);
            if(dist < shortest) {
                shortest = dist;
                shortest_index = j;
            }
        }
        centroidIndexGroups[i] = shortest_index;
    }
    return centroidIndexGroups;
}

double* Kmenas::calculateCenterPoint(double** pointSet[][]) {
    int num = sizeof(pointSet)/sizeof(pointSet[0]);
    double* newCentroid = new double [num];
    for(int i=0; i<DELTA_MATRIX_COLUMN; i++) {
        double sum = 0;
        for(int j=0; j<num; j++) {
            sum += pointSet[j][i];
        }
        newCentroid[i] = (double)sum/num;
    }
    return newCentroid;
}

double** Kmeans::updateCentroids(double centroidIndexGroup[], int k) {
    int num = sizeof(pointSet)/sizeof(pointSet[0]);
    int* groupDataCount = new int [k];
    double** newCentroids = new double* [k];

    for(ink i =0; i<k; i++) {
        newCentroids[i] = new double [DELTA_MATRIX_COLUMN];
        groupDataCount = 0;
    }

    for(int i=0; i<k; i++) {
        for(int j=0; j<DELTA_MATRIX_COLUMN; j++) {
            newCentroids[i][j] = 0;
        }
    }

    for(int i=0; i<num; i++) {
        int groupIndex = centroidIndexGroup[i];
        for(int j=0; j<DELTA_MATRIX_COLUMN; j++) {
            newCentroids[groupIndex][j] += deltaMatrix[i][j];
        }
        groupDataCount[groupIndex] += 1;
    }

    for(int i=0; i<k; i++) {
        for(int j=0; j<DELTA_MATRIX_COLUMN; j++) {
            newCentroids[i][j] = (double)newCentroids[i][j]/groupDataCount[i];
        }
    }
    return newCentroids;
}



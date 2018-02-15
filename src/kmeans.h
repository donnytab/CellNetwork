#ifndef SRC_KMEANS_H_
#define SRC_KMEANS_H_

#include <math.h>
#include <cstdlib>
#include <stdio.h>
#include <limits>

using namespace std;

#define DELTA_MATRIX_ROW 24     // Number of message chunks
#define DELTA_MATRIX_COLUMN 59      // Granularity for each chunk
#define SHORTEST_MAX numeric_limits<double>::max()

class Kmeans {
private:
    double** deltaMatrix;   // Two dimensional array for delta cost
public:
    Kmeans();
    void loadData(double** energyData);
    double static calculateDistance(double array1[], double array2[], int dimension);
    double** generateCentroids(int k);
    int* joinGroup(double** centroids, int k);
    double** updateCentroids(int centroidIndexGroup[], int k);
    double* generateKmeansClusters(double** energyData, int k);
    bool isEqual(int* group1, int* group2, int size);
    double* getRootMeanSquare(double** centroids, int k);
};

#endif

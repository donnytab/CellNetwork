
message EnergyMsg
{
    int source; // User port
    int destination;
    int hopCount = 0;
    long timestamp[60];
    double energyCost[60];
    int priority;   // Kmeans k
}
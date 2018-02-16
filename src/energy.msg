// Energy Message from users to picocells and macrocells
message EnergyMsg
{
    int source; // User port
    int destination;
    int hopCount = 0;
    long timestamp[60];
    double energyCost[60];
    int priority;   // Kmeans k
}
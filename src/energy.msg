// Energy Message from users to picocells and macrocells
message EnergyMsg
{
    int source; // User port, from 0
    int destination;
    int hopCount = 0;
    simtime_t timestamp[60];
    simtime_t enqueueTimestamp;
    simtime_t dequeueTimestamp;
    double energyCost[60];
    int priority;   // Kmeans k
}
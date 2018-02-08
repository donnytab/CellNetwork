
message EnergyMsg
{
    int source;
    int destination;
    int hopCount = 0;
    long timestamp[60];
    double energyCost[60];
}
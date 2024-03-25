struct TspGaConfig{
    unsigned int initialPopulationSize = 100;
    unsigned int chromosomeSize;
    float bestChromosomesPct = 0.25;
    unsigned int maxGenerations = 100;

    unsigned int startPointIndex = 24;
};
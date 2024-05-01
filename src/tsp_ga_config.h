struct TspGaConfig{
    unsigned int initialPopulationSize = 100;
    unsigned int chromosomeSize;
    float bestChromosomesPct = 0.5;
    unsigned int maxGenerations = 20;

    unsigned int startPointIndex = 24;
};
struct TspGaConfig{
    unsigned int initialPopulationSize = 100;
    unsigned int chromosomeSize;
    float bestChromosomesPct = 0.5;
    unsigned int maxGenerations = 50;

    unsigned int startPointIndex = 24;
};
struct TspGaConfig{
    unsigned int initialPopulationSize = 1000;
    unsigned int chromosomeSize;
    float bestChromosomesPct = 0.5f;
    float restChromosomesPct = 0.005f; // Rest of the chromosomes will be transferred to next generation randomly with this percentage
    unsigned int maxGenerations = 100;

    unsigned int startPointIndex = 24;
};
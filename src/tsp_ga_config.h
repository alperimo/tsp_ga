struct TspGaConfig{
    unsigned int initialPopulationSize = 1000;
    unsigned int chromosomeSize;
    float bestChromosomesPct = 0.5f;
    float restChromosomesPct = 0.005f; // Rest of the chromosomes will be transferred to next generation randomly with this percentage
    float eliteChromosomesPct = 0.005f;
    unsigned int maxGenerations = 1000;
    float mutationPatience = 3;
    float mutationRate = 0.25f;

    unsigned int startPointId = 24;
};
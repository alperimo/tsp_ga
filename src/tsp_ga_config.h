struct TspGaConfig{
    unsigned int initialPopulationSize = 1000;
    unsigned int chromosomeSize;

    float bestChromosomesPct = 0.5f;
    float bestChromosomesDecreaseRate = 0.00f;

    float restChromosomesPct = 0.007f; // Rest of the chromosomes will be transferred to next generation randomly with this percentage
    float eliteChromosomesPct = 0.005f;
    unsigned int maxGenerations = 500;

    float mutationPatience = 3;
    float mutationRate = 0.01f;
    float mutationIncreaseRate = 0.001f;

    unsigned int startPointId = 24;
};
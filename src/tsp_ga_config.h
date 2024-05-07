struct TspGaConfig{
    unsigned int initialPopulationSize = 1000;
    unsigned int chromosomeSize;
    float bestChromosomesPct = 0.50f;
    float restChromosomesPct = 0.25; // TODO: Use it to keep some of the worst chromosomes to maintain diversity on selection
    unsigned int maxGenerations = 100;

    unsigned int startPointIndex = 24;
};
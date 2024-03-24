#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include "chromosome.h"

class Population{
    public:
        Population();

        void AddChromosome(const Chromosome& chromosome);
        void ClearPopulation();
        void CreateRandomInitialPopulation();

    private:
        std::vector<Chromosome> population;
};

#endif
#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include "chromosome.h"

class Population{
    public:
        Population();

        void AddChromosome(const Chromosome& chromosome);
        void CalculateFitnessScores();
        void ClearPopulation();
        void GenerateRandomInitialPopulation();
        const auto& GetPopulation() const { return population; }

        void SelectBestChromosomes();

    private:
        std::vector<Chromosome> population;
};

#endif
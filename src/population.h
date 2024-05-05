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

        const auto& GetChromosome(const unsigned int& index) const { return chromosomes.at(index); }
        const auto& GetChromosomes() const { return chromosomes; }
        const auto GetSize() const { return chromosomes.size(); }

        void SelectBestChromosomes();
        void GenerateGenerations(Population& population);

    private:
        std::vector<Chromosome> chromosomes;
};

#endif
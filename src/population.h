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
        int GetSize() const { return chromosomes.size(); }

        void SelectBestChromosomes();

    private:
        std::vector<Chromosome> chromosomes;
};

#endif
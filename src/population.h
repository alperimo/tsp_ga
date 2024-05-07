#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include "chromosome.h"

enum class CrossoverStrategy{
    EveryPair, // Every pair of chromosomes will be crossed,
    SequentialPair, // Each sequential pair of chromosomes will be crossed,
    ShuffledSequentialPair // Populations will be shuffled first and then SequentialPair strategy will be applied
};

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
        auto GenerateSubPopulation(const CrossoverStrategy& crossoverStrategy) -> Population;

        void Shuffle();

    private:
        std::vector<Chromosome> chromosomes;
};

#endif
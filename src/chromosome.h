#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <vector>

class Chromosome{
    public:
        Chromosome();
        Chromosome(const std::vector<unsigned int>& genes);

        void AddGene(unsigned int gene);

        void CalculateFitnessScore();

        double GetFitnessScore() const { return fitnessScore; }
        unsigned int GetGene(const unsigned int& index) const { return genes[index]; }
        unsigned int GetGenSize() const { return static_cast<unsigned int>(genes.size()); }

        void PrintGenes() const;
        void ShuffleGenes();

    private:
        std::vector<unsigned int> genes;
        double fitnessScore = -1.0;
};

#endif
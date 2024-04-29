#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <vector>

class Chromosome{
    public:
        Chromosome(const unsigned int& size = 0);
        Chromosome(const std::vector<unsigned int>& genes);

        void AddGene(unsigned int gene);

        void CalculateFitnessScore();

        long double GetFitnessScore() const { return fitnessScore; }
        unsigned int GetGene(const unsigned int& index) const { return genes.at(index); }
        std::vector<unsigned int>& GetGenes() { return genes; };
        unsigned int GetSize() const { return static_cast<unsigned int>(genes.size()); }

        void PrintGenes() const;
        void ShuffleGenes();

        void SetGene(const unsigned int& index, const unsigned int& gene) { genes.at(index) = gene; }

        auto begin() -> std::vector<unsigned int>::iterator { return genes.begin(); }
        auto end() -> std::vector<unsigned int>::iterator { return genes.end(); }

    private:
        std::vector<unsigned int> genes;
        long double fitnessScore = -1.0;
};

#endif
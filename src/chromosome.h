#include <vector>

class Chromosome{
    public:
        Chromosome();
        Chromosome(const std::vector<unsigned int>& genes);

        void AddGene(unsigned int gene);

        void PrintGenes() const;
        void ShuffleGenes();

    private:
        std::vector<unsigned int> genes;
};
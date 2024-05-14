#include "mutation.h"
#include "crossover.h"

Mutation::Mutation(){}  

void Mutation::ApplySwap(Chromosome& chromosome, float mutationRate){
    int chromosomeSize = chromosome.GetSize();
    auto indices = Crossover::GetTwoCrossoverPointIndices(chromosomeSize);
    //std::cout<<"Swapping "<<indices.first<<" and "<<indices.second<<std::endl;

    if (rand() % 100 < mutationRate * 100){
        const auto temp_gene = chromosome.GetGene(indices.first);
        chromosome.SetGene(indices.first, chromosome.GetGene(indices.second));
        chromosome.SetGene(indices.second, temp_gene);
    }
}


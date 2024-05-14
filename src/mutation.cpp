#include "mutation.h"
#include "crossover.h"

Mutation::Mutation(){}  

Chromosome Mutation::ApplySwap(const Chromosome& chromosome, float mutationRate){
    int chromosomeSize = chromosome.GetSize();
    auto indices = Crossover::GetTwoCrossoverPointIndices(chromosomeSize);
    Chromosome newChromosome = chromosome;
    auto temp_gene = newChromosome.GetGene(indices.first);

    //std::cout<<"Swapping "<<indices.first<<" and "<<indices.second<<std::endl;

    if (rand() % 100 < mutationRate * 100){
        newChromosome.SetGene(indices.first, newChromosome.GetGene(indices.second));
        newChromosome.SetGene(indices.second, temp_gene);
    }

    return newChromosome;
}

Chromosome Mutation::ApplyScramble(const Chromosome& chromosome, float mutationRate){
    int chromosomeSize = chromosome.GetSize();
    auto indices = Crossover::GetTwoCrossoverPointIndices(chromosomeSize);
    Chromosome newChromosome = chromosome;
    std::vector<unsigned int> scrambledGenes;

    for (int i = indices.first; i <= indices.second; i++){
        scrambledGenes.push_back(newChromosome.GetGene(i));
    }

    std::random_shuffle(scrambledGenes.begin(), scrambledGenes.end());

    for (int i = indices.first; i <= indices.second; i++){
        newChromosome.SetGene(i, scrambledGenes[i - indices.first]);
    }

    return newChromosome;
}

Chromosome Mutation::ApplyInversion(const Chromosome& chromosome, float mutationRate){
    int chromosomeSize = chromosome.GetSize();
    auto indices = Crossover::GetTwoCrossoverPointIndices(chromosomeSize);
    Chromosome newChromosome = chromosome;
    std::vector<unsigned int> invertedGenes;

    for (int i = indices.first; i <= indices.second; i++){
        invertedGenes.push_back(newChromosome.GetGene(i));
    }

    std::reverse(invertedGenes.begin(), invertedGenes.end());

    for (int i = indices.first; i <= indices.second; i++){
        newChromosome.SetGene(i, invertedGenes[i - indices.first]);
    }

    return newChromosome;
}


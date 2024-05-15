#include "mutation.h"
#include "crossover.h"
#include "tsp_ga_config.h"

Mutation::Mutation(){}  

TspGaConfig config;

void Mutation::ApplySwap(Chromosome& chromosome){
    int chromosomeSize = chromosome.GetSize();
    auto indices = Crossover::GetTwoCrossoverPointIndices(chromosomeSize);
    auto temp_gene = chromosome.GetGene(indices.first);

    //std::cout<<"Swapping "<<indices.first<<" and "<<indices.second<<std::endl;

    if (rand() % 100 < config.mutationRate * 100){
        chromosome.SetGene(indices.first, chromosome.GetGene(indices.second));
        chromosome.SetGene(indices.second, temp_gene);
    }
}

void Mutation::ApplyScramble(Chromosome& chromosome){
    int chromosomeSize = chromosome.GetSize();
    auto indices = Crossover::GetTwoCrossoverPointIndices(chromosomeSize);
    
    if(rand() % 100 < config.mutationRate * 100){
        std::vector<unsigned int> scrambledGenes;
        for (int i = indices.first; i <= indices.second; i++){
            scrambledGenes.push_back(chromosome.GetGene(i));
        }

        std::random_shuffle(scrambledGenes.begin(), scrambledGenes.end());

        for (int i = indices.first; i <= indices.second; i++){
            chromosome.SetGene(i, scrambledGenes[i - indices.first]);
        }
    }
}

void Mutation::ApplyInversion(Chromosome& chromosome){
    int chromosomeSize = chromosome.GetSize();
    auto indices = Crossover::GetTwoCrossoverPointIndices(chromosomeSize);
    
    if (rand() % 100 < config.mutationRate * 100){
        std::vector<unsigned int> invertedGenes;

        for (int i = indices.first; i <= indices.second; i++){
            invertedGenes.push_back(chromosome.GetGene(i));
        }

        std::reverse(invertedGenes.begin(), invertedGenes.end());

        for (int i = indices.first; i <= indices.second; i++){
            chromosome.SetGene(i, invertedGenes[i - indices.first]);
        }
    }
}


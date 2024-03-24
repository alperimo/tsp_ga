#include "chromosome.h"
#include <algorithm>
#include <random>
#include <iostream>

Chromosome::Chromosome(){}

Chromosome::Chromosome(const std::vector<unsigned int>& genes_) : genes(genes_)
{
    
}

void Chromosome::AddGene(unsigned int gene){
    genes.push_back(gene);
}

void Chromosome::PrintGenes() const{
    for (auto gene : genes){
        std::cout << gene << " ";
    }
}

void Chromosome::ShuffleGenes(){
    std::shuffle(genes.begin(), genes.end(), std::mt19937(std::random_device{}()));
}
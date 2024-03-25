#include "chromosome.h"
#include "tsp_ga.h"
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

void Chromosome::CalculateFitnessScore(){
    this->fitnessScore = 0.0;
    auto genSize = GetGenSize();

    for (unsigned int geneIndex = 0; geneIndex < genSize - 1; geneIndex++){
        auto distance = TspGa::distanceHelper.GetDistanceByPointIndex(genes[geneIndex], genes[geneIndex + 1]);
        this->fitnessScore += distance;
    }

    this->fitnessScore += TspGa::distanceHelper.GetDistanceByPointIndex(genes[genSize - 1], genes[0]);

    std::cout << "Fitness Score: " << this->fitnessScore << std::endl;
}

void Chromosome::PrintGenes() const{
    for (auto gene : genes){
        std::cout << gene << " ";
    }
}

void Chromosome::ShuffleGenes(){
    std::shuffle(genes.begin() + 1, genes.end() - 1, std::mt19937(std::random_device{}()));
}
#include "chromosome.h"
#include "tsp_ga.h"
#include <algorithm>
#include <random>
#include <iostream>

Chromosome::Chromosome(const unsigned int& size){
    genes = std::vector<unsigned int>(size);
}

Chromosome::Chromosome(const std::vector<unsigned int>& genes_) : genes(genes_)
{
    
}

void Chromosome::AddGene(unsigned int gene){
    genes.push_back(gene);
}

void Chromosome::CalculateFitnessScore(){
    this->fitnessScore = 0.0;
    auto size = GetSize();

    for (unsigned int geneIndex = 0; geneIndex < size - 1; geneIndex++){
        auto distance = TspGa::distanceHelper.GetDistanceByPointId(genes[geneIndex], genes[geneIndex + 1]);
        this->fitnessScore += distance;
    }

    this->fitnessScore += TspGa::distanceHelper.GetDistanceByPointId(genes[size - 1], genes[0]);
}

void Chromosome::PrintGenes() const{
    for (auto gene : genes){
        std::cout << gene << " ";
    }

    std::cout << genes.at(0) << " ";
}

void Chromosome::ShuffleGenes(){
    std::shuffle(genes.begin() + 1, genes.end(), std::mt19937(std::random_device{}()));
}
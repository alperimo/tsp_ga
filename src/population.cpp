#include "population.h"
#include "tsp_ga.h"
#include <iostream>
#include <algorithm>
#include <random>
#include "crossover.h"

Population::Population(){
    // Constructor
}

void Population::AddChromosome(const Chromosome& chromosome){
    chromosomes.push_back(chromosome);
}

void Population::CalculateFitnessScores(){
    for (auto& chromosome : chromosomes){
        chromosome.CalculateFitnessScore();
    }
}

void Population::ClearPopulation(){
    chromosomes.clear();
}

void Population::GenerateRandomInitialPopulation(){
    this->ClearPopulation();

    auto startPointIndex = TspGa::config.startPointIndex;

    Chromosome chromosome;
    chromosome.AddGene(startPointIndex);
    for (unsigned int geneIndex = 0; geneIndex < TspGa::config.chromosomeSize; geneIndex++){
        if (geneIndex == startPointIndex){
            continue;
        }

        chromosome.AddGene(geneIndex);
    }

    for (unsigned int chromosomeIndex = 0; chromosomeIndex < TspGa::config.initialPopulationSize; chromosomeIndex++){
        chromosome.ShuffleGenes();
        std::cout << "Chromosome " << chromosomeIndex << ": ";
        chromosome.PrintGenes();

        std::cout << std::endl << " -------------------------------------- " << std::endl;

        this->AddChromosome(chromosome);
    }

    this->CalculateFitnessScores();
}

void Population::SelectBestChromosomes(){
    std::cout << "Selecting Best Chromosomes" << std::endl;

    std::sort(chromosomes.begin(), chromosomes.end(), [](const Chromosome& c1, const Chromosome& c2){
        return c1.GetFitnessScore() < c2.GetFitnessScore();
    });

    const double eraseSize = static_cast<double>(chromosomes.size()) * TspGa::config.bestChromosomesPct;
    auto firstIndexToRemove = static_cast<decltype(chromosomes.begin())::difference_type>(eraseSize);
    chromosomes.erase(chromosomes.begin() + firstIndexToRemove, chromosomes.end());
}
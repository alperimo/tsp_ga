#include "population.h"
#include "tsp_ga.h"
#include <iostream>
#include <algorithm>
#include <random>

Population::Population(){
    // Constructor
}

void Population::AddChromosome(const Chromosome& chromosome){
    population.push_back(chromosome);
}

void Population::CalculateFitnessScores(){
    for (auto& chromosome : population){
        chromosome.CalculateFitnessScore();
    }
}

void Population::ClearPopulation(){
    population.clear();
}

void Population::GenerateRandomInitialPopulation(){
    this->ClearPopulation();

    Chromosome chromosome;
    for (unsigned int geneIndex = 0; geneIndex < TspGa::config.chromosomeSize; geneIndex++){
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

    std::sort(population.begin(), population.end(), [](const Chromosome& c1, const Chromosome& c2){
        return c1.GetFitnessScore() < c2.GetFitnessScore();
    });

    const double eraseSize = static_cast<double>(population.size()) * TspGa::config.bestChromosomesPct;
    auto firstIndexToRemove = static_cast<decltype(population.begin())::difference_type>(eraseSize);
    population.erase(population.begin() + firstIndexToRemove, population.end());
}
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

void Population::ClearPopulation(){
    population.clear();
}

void Population::CreateRandomInitialPopulation(){
    this->ClearPopulation();

    Chromosome chromosome;
    for (unsigned int geneIndex = 1; geneIndex < TspGa::config.chromosomeSize + 1; geneIndex++){
        chromosome.AddGene(geneIndex);
    }

    for (unsigned int chromosomeIndex = 0; chromosomeIndex < TspGa::config.populationSize; chromosomeIndex++){
        chromosome.ShuffleGenes();
        std::cout << "Chromosome " << chromosomeIndex << ": ";
        chromosome.PrintGenes();
        
        std::cout << std::endl << " -------------------------------------- " << std::endl;

        this->AddChromosome(chromosome);
    }
}
#include "population.h"
#include "tsp_ga.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <tuple>
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

// TODO: Keep also some of the worst chromosomes to maintain diversity
void Population::SelectBestChromosomes(){
    std::cout << "Selecting Best Chromosomes..." << std::endl;

    std::sort(chromosomes.begin(), chromosomes.end(), [](const Chromosome& c1, const Chromosome& c2){
        return c1.GetFitnessScore() < c2.GetFitnessScore();
    });

    const double eraseSize = static_cast<double>(chromosomes.size()) * TspGa::config.bestChromosomesPct;
    auto firstIndexToRemove = static_cast<decltype(chromosomes.begin())::difference_type>(eraseSize);
    chromosomes.erase(chromosomes.begin() + firstIndexToRemove, chromosomes.end());

    if (TspGa::bestChromosome.GetSize() == 0 || GetChromosome(0).GetFitnessScore() < TspGa::bestChromosome.GetFitnessScore()){
        TspGa::bestChromosome = GetChromosome(0);
    }
}

void Population::GenerateGenerations(Population& population){
    auto [createdGenerationCount, maxGenerations] = std::make_tuple(0u, TspGa::config.maxGenerations); 
    auto& bestChromosome = TspGa::bestChromosome;

    auto doCrossovers = [&]{
        std::cout << "Population Size: " << population.GetSize() << std::endl;

        Population populationOffspring;
        
        // TODO: Try to use std::tuple instead of OffspringPair struct with cpp17+ [Now we get structured bindings error with std::tuple<std::pair<...>, std::pair<...>>]
        struct OffspringPair {
            std::pair<Chromosome, Chromosome> offSprings1;
            std::pair<Chromosome, Chromosome> offSprings2;
        };

        // Partially mapped crossover where 2 crossover happens with each chromosome
        for (auto i = 0u; i < population.GetSize()-2; i += 1) {
            auto createOffspringPairs = [&](const Chromosome& chromosome1, const Chromosome& chromosome2) -> OffspringPair{
                auto offSprings1 = Crossover::ApplyPartiallyMapped(chromosome1, chromosome2);
                auto offSprings2 = Crossover::ApplyPartiallyMapped(chromosome1, chromosome2);

                offSprings1.first.CalculateFitnessScore();
                offSprings1.second.CalculateFitnessScore();

                offSprings2.first.CalculateFitnessScore();
                offSprings2.second.CalculateFitnessScore();

                std::cout << std::endl << std::endl;

                return {offSprings1, offSprings2};
            };

            auto chooseAndAddBetterOffspring = [&](Chromosome& offspring1, Chromosome& offspring2){
                auto& betterOffspring = offspring1.GetFitnessScore() <= offspring2.GetFitnessScore() ? offspring1 : offspring2;
                populationOffspring.AddChromosome(betterOffspring);
            };

            auto [offSprings1, offSprings2] = createOffspringPairs(population.GetChromosome(i), population.GetChromosome(i+1));

            chooseAndAddBetterOffspring(offSprings1.first, offSprings1.second);
            chooseAndAddBetterOffspring(offSprings2.first, offSprings2.second);
        }

        population = std::move(populationOffspring);
        createdGenerationCount++; 
        
        std::cout << std::endl << "Remaning Generations: " << maxGenerations - createdGenerationCount << std::endl;
    };
    
    while (population.GetSize() > 4){
        population.SelectBestChromosomes();
        doCrossovers();
        population.CalculateFitnessScores();
        
        std::cout << "Best Solution for the Generation " << createdGenerationCount << ": " << population.GetChromosome(0).GetFitnessScore() << std::endl;

        if (createdGenerationCount == maxGenerations){
            std::cout << "Number of maximum generations have been reached. Exiting..." << std::endl;
            std::cout << "\nBest Solution: " << bestChromosome.GetFitnessScore() <<std::endl;
            bestChromosome.PrintGenes();
            return;
        }
    }

    std::cout << "There are no any chromosomes to crossover..." << std::endl;
    std::cout << "Best Solution: " << bestChromosome.GetFitnessScore() << std::endl;
    bestChromosome.PrintGenes(); 
}
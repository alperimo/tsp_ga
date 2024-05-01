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

// TODO: Keep also some of the worst chromosomes to maintain diversity
void Population::SelectBestChromosomes(){
    std::cout << "Selecting Best Chromosomes..." << std::endl;

    std::sort(chromosomes.begin(), chromosomes.end(), [](const Chromosome& c1, const Chromosome& c2){
        return c1.GetFitnessScore() < c2.GetFitnessScore();
    });

    const double eraseSize = static_cast<double>(chromosomes.size()) * TspGa::config.bestChromosomesPct;
    auto firstIndexToRemove = static_cast<decltype(chromosomes.begin())::difference_type>(eraseSize);
    chromosomes.erase(chromosomes.begin() + firstIndexToRemove, chromosomes.end());
}

int pairCounter = 1;

void Population::GenerateGenerations(int maxGen, Chromosome& bestChromosome, Population& population, Population populationOffspring){

    std::cout << "\nRemaning Generations: " << maxGen << std::endl;
    if (maxGen == 0){
        std::cout << "Number of maximum generations have been reached. Exiting..." << std::endl;
        std::cout << "\nBest Solution: " << bestChromosome.GetFitnessScore() <<std::endl;
        bestChromosome.PrintGenes();   
        exit(0);
    }

    population.SelectBestChromosomes();
    if (population.GetSize() < 4){
        std::cout << "No more chromosomes to crossover. Exiting..." << std::endl;
        std::cout << "\nBest Solution: " << population.GetChromosome(0).GetFitnessScore() << std::endl;
        population.GetChromosome(0).PrintGenes(); 
        exit(0);
    }
    std::cout << "Population Size: " << population.GetSize() << std::endl;
    
    /*
    std::cout << "Best Chromosomes: " << std::endl;
    for (const auto& chromosome : population.GetChromosomes()){
        chromosome.PrintGenes();
        std::cout << std::endl << " Fitness Score: " << chromosome.GetFitnessScore() << std::endl;
        std::cout << " -------------------------------------- " << std::endl;
    }
    */

    // Partially mapped crossover where 2 crossover happens with each chromosome
    for (int i = 0; i < population.GetSize()-2; i += 1) {
        std::cout << "\n---Applying partially mapped crossover two times---";
        // Apply partially mapped crossover to chromosome i and chromosome i+1
        auto offSprings1 = Crossover::ApplyPartiallyMapped(population.GetChromosome(i), population.GetChromosome(i + 1));
        std::cout << std::endl;

        // Calculate fitness for offspring 1
        offSprings1.first.CalculateFitnessScore();
        offSprings1.second.CalculateFitnessScore();

        // Apply partially mapped crossover to chromosome i and chromosome i+2
        auto offSprings2 = Crossover::ApplyPartiallyMapped(population.GetChromosome(i), population.GetChromosome(i + 2));
        std::cout << std::endl;

        // Calculate fitness for offspring 2
        offSprings2.first.CalculateFitnessScore();
        offSprings2.second.CalculateFitnessScore();

        // Choose the better offspring from each pair
        if (offSprings1.first.GetFitnessScore() <= offSprings1.second.GetFitnessScore()) {
            std::cout << "Best Offspring Fitness Score from Pair " << pairCounter << ": " << offSprings1.first.GetFitnessScore() << std::endl;
            
            populationOffspring.AddChromosome(offSprings1.first);
            if(offSprings1.first.GetFitnessScore() < bestChromosome.GetFitnessScore()){
                bestChromosome = offSprings1.first;
            }
        } else {
            std::cout << "Best Offspring Fitness Score from Pair " << pairCounter << ": " << offSprings1.second.GetFitnessScore() << std::endl;
            populationOffspring.AddChromosome(offSprings1.second);
            if(offSprings1.second.GetFitnessScore() < bestChromosome.GetFitnessScore()){
                bestChromosome = offSprings1.second;
            }
        }

        pairCounter++;
        
        if (offSprings2.first.GetFitnessScore() <= offSprings2.second.GetFitnessScore()) {
            std::cout << "Best Offspring Fitness Score from Pair " << pairCounter << ": " << offSprings2.first.GetFitnessScore() << std::endl;
            offSprings2.first.GetFitnessScore();
            populationOffspring.AddChromosome(offSprings2.first);
            if(offSprings2.first.GetFitnessScore() < bestChromosome.GetFitnessScore()){
                bestChromosome = offSprings2.first;
            }
        } else {
            std::cout << "Best Offspring Fitness Score from Pair " << pairCounter << ": " << offSprings2.second.GetFitnessScore() << std::endl;
            offSprings2.second.GetFitnessScore();
            populationOffspring.AddChromosome(offSprings2.second);
            if(offSprings2.second.GetFitnessScore() < bestChromosome.GetFitnessScore()){
                bestChromosome = offSprings2.second;
            }
        }
        pairCounter++;
        std::cout << "Best Solution after Crossovers: " << populationOffspring.GetChromosome(0).GetFitnessScore() << std::endl;
        std::cout << "*******************************************\n";
    }
    
    maxGen -= 1;
    
    population.ClearPopulation();
    for(auto& chromosome : populationOffspring.GetChromosomes()){
        population.AddChromosome(chromosome);
    }
    populationOffspring.ClearPopulation();
    GenerateGenerations(maxGen, bestChromosome, population, populationOffspring);
}
#include <iostream>
#include "tsp_ga.h"
#include "population.h"
#include <array>
#include <algorithm>
#include <random>
#include <tuple>

TspGaConfig TspGa::config;
DistanceHelper TspGa::distanceHelper;
Chromosome TspGa::bestChromosome;

TspGa::TspGa(){
    // Constructor
}

auto TspGa::GetPoints() -> std::vector<Point>&{
    return points;
}

void TspGa::InitPopulation(){
    std::cout << "Initializing Population" << std::endl;

    this->points = fileReader.ParseCsv("../data/tsp81cities_coords.csv");
    
    config.chromosomeSize = static_cast<unsigned int>(points.size());

    distanceHelper.CreateDistanceMatrixFromPoints(points);

    std::cout << "Distance between point index 0 and 1: " << distanceHelper.GetDistanceByPointIndex(0, 1) << std::endl;
    std::cout << "Distance between point index 7 and 18: " << distanceHelper.GetDistanceByPointIndex(7, 18) << std::endl;

    std::cout << "Distance between point index 55 and 56: " << distanceHelper.GetDistanceByPointIndex(55, 56) << std::endl;
    std::cout << "Distance between point index 50 and 81: " << distanceHelper.GetDistanceByPointIndex(50, 81) << std::endl;

    population.GenerateRandomInitialPopulation();
}

void TspGa::CreateGenerations(Population& parentPopulation){
    auto [createdGenerationCount, maxGenerations] = std::make_tuple(0u, TspGa::config.maxGenerations);

    while (parentPopulation.GetSize() > 4){
        parentPopulation.SelectBestChromosomes();

        std::cout << "Best Solution for the Generation " << createdGenerationCount << ": " << parentPopulation.GetChromosome(0).GetFitnessScore() << std::endl;

        if (bestChromosome.GetSize() == 0 || parentPopulation.GetChromosome(0).GetFitnessScore() < bestChromosome.GetFitnessScore()){
            bestChromosome = parentPopulation.GetChromosome(0);
        }

        parentPopulation = std::move(parentPopulation.GenerateSubPopulation());
        parentPopulation.CalculateFitnessScores();

        createdGenerationCount++;
        
        if (createdGenerationCount == maxGenerations){
            std::cout << "Number of maximum generations have been reached." << std::endl << std::endl;
            std::cout << "Best Solution: " << bestChromosome.GetFitnessScore() <<std::endl;
            bestChromosome.PrintGenes();
            return;
        }
    }

    std::cout << "There are no any enough chromosomes to crossover..." << std::endl;
    std::cout << "Best Solution: " << bestChromosome.GetFitnessScore() << std::endl;
    bestChromosome.PrintGenes();
}

void TspGa::Solve(){    
    TestCrossovers();

    CreateGenerations(this->population);
}

// TODO: Just for tests, remove this function later.
void TspGa::TestCrossovers(){
    std::cout << "Testing Crossovers" << std::endl;
    
    Population generation;
    population.SelectBestChromosomes();

    std::cout << "Best Chromosomes: " << std::endl;
    for (const auto& chromosome : population.GetChromosomes()){
        chromosome.PrintGenes();
        std::cout << std::endl << " Fitness Score: " << chromosome.GetFitnessScore() << std::endl;
        std::cout << " -------------------------------------- " << std::endl;
    }

    // Test Crossover for the best two chromosomes
    std::cout << "Applying partially mapped crossover to best two chromosomes" << std::endl;
    auto offSprings = Crossover::ApplyPartiallyMapped(population.GetChromosome(0), population.GetChromosome(1));
    
    std::cout << "Offspring 1: ";
    offSprings.first.PrintGenes();
    std::cout << std::endl;

    std::cout << "Offspring 2: ";
    offSprings.second.PrintGenes();
    std::cout << std::endl;

    // Test for order based crossover
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Applying order based crossover to best two chromosomes" << std::endl;
    offSprings = Crossover::ApplyOrderBased(population.GetChromosome(0), population.GetChromosome(1));
    
    std::cout << "Offspring 1: ";
    offSprings.first.PrintGenes();
    std::cout << std::endl;

    std::cout << "Offspring 2: ";
    offSprings.second.PrintGenes();
    std::cout << std::endl;

    // Test for cycle crossover
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "Applying cycle crossover to best two chromosomes" << std::endl;

    std::cout << "Parent 1: ";
    population.GetChromosome(0).PrintGenes();
    std::cout << std::endl;

    std::cout << "Parent 2: ";
    population.GetChromosome(1).PrintGenes();
    std::cout << std::endl;

    offSprings = Crossover::ApplyCycleBased(population.GetChromosome(0), population.GetChromosome(1));

    std::cout << "Offspring 1: ";
    offSprings.first.PrintGenes();
    std::cout << std::endl;

    std::cout << "Offspring 2: ";
    offSprings.second.PrintGenes();
    std::cout << std::endl;
}
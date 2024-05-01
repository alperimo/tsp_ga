#include <iostream>
#include "tsp_ga.h"
#include <array>
#include <algorithm>
#include <random>

TspGaConfig TspGa::config;
DistanceHelper TspGa::distanceHelper;
static int maxGen = TspGa::config.maxGenerations;
Chromosome bestChromosome = NULL;

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
    bestChromosome = population.GetChromosome(0);
}

void TspGa::Solve(){

    Population populationOffspring;

    std::cout << "Remaning Generations: " << maxGen << std::endl;
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
        std::cout << "\nApplying partially mapped crossover" << std::endl;

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
        if (offSprings1.first.GetFitnessScore() < offSprings1.second.GetFitnessScore()) {
            std::cout << "Best Offspring Fitness Score from Pair " << i + 1 << ": " << offSprings1.first.GetFitnessScore() << std::endl;
            
            populationOffspring.AddChromosome(offSprings1.first);
            if(offSprings1.first.GetFitnessScore() < bestChromosome.GetFitnessScore()){
                bestChromosome = offSprings1.first;
            }
        } else {
            std::cout << "Best Offspring Fitness Score from Pair " << i + 1 << ": " << offSprings1.second.GetFitnessScore() << std::endl;
            populationOffspring.AddChromosome(offSprings1.second);
            if(offSprings1.second.GetFitnessScore() < bestChromosome.GetFitnessScore()){
                bestChromosome = offSprings1.second;
            }
        }
        if (offSprings2.first.GetFitnessScore() < offSprings2.second.GetFitnessScore()) {
            std::cout << "Best Offspring Fitness Score from Pair " << i + 2 << ": " << offSprings2.first.GetFitnessScore() << std::endl;
            offSprings2.first.GetFitnessScore();
            populationOffspring.AddChromosome(offSprings2.first);
            if(offSprings2.first.GetFitnessScore() < bestChromosome.GetFitnessScore()){
                bestChromosome = offSprings2.first;
            }
        } else {
            std::cout << "Best Offspring Fitness Score from Pair " << i + 2 << ": " << offSprings2.second.GetFitnessScore() << std::endl;
            offSprings2.second.GetFitnessScore();
            populationOffspring.AddChromosome(offSprings2.second);
            if(offSprings2.second.GetFitnessScore() < bestChromosome.GetFitnessScore()){
                bestChromosome = offSprings2.second;
            }
        }
        std::cout << "Best Solution within this population: " << population.GetChromosome(0).GetFitnessScore() << std::endl;
    }
    
    maxGen -= 1;
    
    population.ClearPopulation();
    for(auto& chromosome : populationOffspring.GetChromosomes()){
        population.AddChromosome(chromosome);
    }
    populationOffspring.ClearPopulation();
    TspGa::Solve(); 
}
#include <iostream>
#include "tsp_ga.h"
#include <array>
#include <algorithm>
#include <random>

TspGaConfig TspGa::config;
DistanceHelper TspGa::distanceHelper;

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

void TspGa::Solve(){
    std::cout << "Running TspGa Solver using Genetic Algorithm" << std::endl;

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

    std::cout << "Applying order based crossover to best two chromosomes" << std::endl;
    offSprings = Crossover::ApplyOrderBased(population.GetChromosome(0), population.GetChromosome(1));
    
    std::cout << "Offspring 1: ";
    offSprings.first.PrintGenes();
    std::cout << std::endl;

    std::cout << "Offspring 2: ";
    offSprings.second.PrintGenes();
    std::cout << std::endl;

}
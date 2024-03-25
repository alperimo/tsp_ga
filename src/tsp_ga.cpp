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

void TspGa::InitPopulation(){
    std::cout << "Initializing Population" << std::endl;

    this->points = fileReader.ParseCsv("../data/tsp81cities_coords.csv");
    
    config.chromosomeSize = static_cast<unsigned int>(points.size());

    distanceHelper.CreateDistanceMatrixFromPoints(points);

    std::cout << "Distance between point index 0 and 1: " << distanceHelper.GetDistanceByPointIndex(0, 1) << std::endl;
    std::cout << "Distance between point index 7 and 18: " << distanceHelper.GetDistanceByPointIndex(7, 18) << std::endl;

    std::cout << "Distance between point index 55 and 56: " << distanceHelper.GetDistanceByPointIndex(55, 56) << std::endl;

    population.GenerateRandomInitialPopulation();
}

void TspGa::Solve(){
    std::cout << "Running TspGa Solver using Genetic Algorithm" << std::endl;

    /*population.SelectBestChromosomes();
    
    std::cout << "Best Chromosomes: " << std::endl;
    for (const auto& chromosome : population.GetPopulation()){
        chromosome.PrintGenes();
        std::cout << std::endl << " Fitness Score: " << chromosome.CalculateFitnessScore() << std::endl;
        std::cout << " -------------------------------------- " << std::endl;
    }*/
}
#include <iostream>
#include "tsp_ga.h"
#include "population.h"
#include <array>
#include <algorithm>
#include <random>

TspGaConfig TspGa::config;
DistanceHelper TspGa::distanceHelper;
static int maxGen = TspGa::config.maxGenerations;
Chromosome bestChromosome;

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
    bestChromosome = population.GetChromosome(0); //Random chromosome
}

void TspGa::Solve(){

    Population generation;
    Population populationOffspring;

    generation.GenerateGenerations(maxGen, bestChromosome, population, populationOffspring);
}
#include <iostream>
#include "tsp_ga.h"
#include <array>
#include <algorithm>
#include <random>

TspGaConfig TspGa::config;

TspGa::TspGa(){
    // Constructor
}

void TspGa::Solve(){
    std::cout << "Running TspGa Solver using Genetic Algorithm" << std::endl;

    this->points = fileReader.ParseCsv("../data/tsp81cities_coords.csv");
    
    config.chromosomeSize = static_cast<unsigned int>(points.size());

    distanceHelper.CreateDistanceMatrixFromPoints(points);
    std::cout << "Distance between point index 55 and 56: " << distanceHelper.GetDistanceByPointIndex(55, 56) << std::endl;

    population.CreateRandomInitialPopulation();
}
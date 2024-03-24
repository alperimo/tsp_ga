#include <iostream>
#include "tsp_ga.h"

TspGaConfig TspGa::gaConfig;

TspGa::TspGa(){
    // Constructor
}

void TspGa::Solve(){
    std::cout << "Running TspGa Solver using Genetic Algorithm" << std::endl;

    auto points = fileReader.ParseCsv("../data/tsp81cities_coords.csv");
    
    gaConfig.chromosomeSize = points.size();

    distanceHelper.CreateDistanceMatrixFromPoints(points);

    std::cout << "Distance between point index 55 and 56: " << distanceHelper.GetDistanceByPointIndex(55, 56) << std::endl;
}
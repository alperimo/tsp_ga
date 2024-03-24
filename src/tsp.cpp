#include <iostream>
#include "tsp.h"

Tsp::Tsp(){
    // Constructor
}

void Tsp::Run(){
    std::cout << "Running TSP" << std::endl;
    auto points = file_reader.ParseCsv("../data/tsp81cities_coords.csv");
    
    distance_helper.CreateDistanceMatrixFromPoints(points);

    std::cout << "Distance between point index 55 and 56: " << distance_helper.GetDistanceByPointIndex(55, 56) << std::endl;
}
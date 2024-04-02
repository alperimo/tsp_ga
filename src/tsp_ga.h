#ifndef TSP_H
#define TSP_H

#include "file_reader.h"
#include "distance_helper.h"
#include "tsp_ga_config.h"
#include "population.h"
#include "crossover.h"

class TspGa{
    public:
        TspGa();

        auto GetPoints() -> std::vector<Point>&;

        void InitPopulation();
        void Solve();

        static TspGaConfig config;
        static DistanceHelper distanceHelper;
        static Crossover crossover;

    private:
        FileReader fileReader;

        std::vector<Point> points;
        Population population;
};

#endif
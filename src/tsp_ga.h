#ifndef TSP_H
#define TSP_H

#include "file_reader.h"
#include "distance_helper.h"
#include "tsp_ga_config.h"
#include "population.h"

class TspGa{
    public:
        TspGa();

        void Solve();

        static TspGaConfig config;
    
    private:
        FileReader fileReader;
        DistanceHelper distanceHelper;

        std::vector<Point> points;
        Population population;
};

#endif
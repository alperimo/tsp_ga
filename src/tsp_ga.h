#ifndef TSP_H
#define TSP_H

#include "file_reader.h"
#include "distance_helper.h"
#include "tsp_ga_config.h"

class TspGa{
    public:
        TspGa();

        void Solve();

        static TspGaConfig gaConfig;
    
    private:
        FileReader fileReader;
        DistanceHelper distanceHelper;
};

#endif
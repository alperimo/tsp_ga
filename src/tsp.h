#ifndef TSP_H
#define TSP_H

#include "file_reader.h"
#include "distance_helper.h"

class Tsp{
    public:
        Tsp();

        void Run();
    
    private:
        FileReader file_reader;
        DistanceHelper distance_helper;
};

#endif
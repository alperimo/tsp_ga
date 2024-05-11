#ifndef DISTANCE_HELPER_H
#define DISTANCE_HELPER_H

#include <vector>

#include "point.h"

#define RADIO_TIERRA 6371.0

class DistanceHelper{
    public:
        DistanceHelper();

        long double CalculateDistance(const Point& point1, const Point& point2);
        void CreateDistanceMatrixFromPoints(const std::vector<Point>& points);
        
        long double GetDistanceByPointId(const unsigned int& pointId1, const unsigned int& pointId2);
        const auto& GetDistanceMatrix() const { return distanceMatrix; }

        long double ToRadians(const long double& degree);
    private:
        std::vector<std::vector<long double>> distanceMatrix;
};

#endif
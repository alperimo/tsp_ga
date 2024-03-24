#ifndef DISTANCE_HELPER_H
#define DISTANCE_HELPER_H

#include <vector>

#include "point.h"

class DistanceHelper{
    public:
        DistanceHelper();

        double CalculateDistance(const Point& point1, const Point& point2);
        void CreateDistanceMatrixFromPoints(const std::vector<Point>& points);
        
        const double GetDistanceByPointIndex(const unsigned int& pointIndex1, const unsigned int& pointIndex2);
        const auto GetDistanceMatrix() const { return distanceMatrix; }

    private:
        std::vector<std::vector<double>> distanceMatrix;
};

#endif
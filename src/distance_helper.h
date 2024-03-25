#ifndef DISTANCE_HELPER_H
#define DISTANCE_HELPER_H

#include <vector>

#include "point.h"

#define M_PI 3.14159265358979323846
#define RADIO_TIERRA 6371.0

class DistanceHelper{
    public:
        DistanceHelper();

        long double CalculateDistance(const Point& point1, const Point& point2);
        void CreateDistanceMatrixFromPoints(const std::vector<Point>& points);
        
        long double GetDistanceByPointIndex(const unsigned int& pointIndex1, const unsigned int& pointIndex2);
        const auto& GetDistanceMatrix() const { return distanceMatrix; }

        long double ToRadians(const long double& degree);
    private:
        std::vector<std::vector<long double>> distanceMatrix;
};

#endif
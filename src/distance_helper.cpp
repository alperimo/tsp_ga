#include <math.h>

#include "distance_helper.h"

DistanceHelper::DistanceHelper(){
    // Constructor
}

double DistanceHelper::CalculateDistance(const Point& point1, const Point& point2){
    auto point1Lat = point1.GetLatitude(), point1Lon = point1.GetLongitude();
    auto point2Lat = point2.GetLatitude(), point2Lon = point2.GetLongitude();

    auto dLat = (point2Lat - point1Lat) * M_PI / 180.0;
    auto dLon = (point2Lon - point1Lon) * M_PI / 180.0;

    auto a = sin(dLat / 2) * sin(dLat / 2) + cos(point1Lat * M_PI / 180.0) * cos(point2Lat * M_PI / 180.0) * sin(dLon / 2) * sin(dLon / 2);
    auto c = 2 * atan2(sqrt(a), sqrt(1 - a));
    
    return 6371 * c;
}

void DistanceHelper::CreateDistanceMatrixFromPoints(const std::vector<Point>& points) {
    auto totalPoints = points.size();
    
    this->distanceMatrix = std::vector<std::vector<double>>(totalPoints, std::vector<double>(totalPoints, 0.0));
    
    for (unsigned int i = 0; i < totalPoints; i++) {
        for (unsigned int j = 0; j < totalPoints; j++) {
            if (i == j) {
                this->distanceMatrix[i][j] = 0.0;
            } else {
                this->distanceMatrix[i][j] = this->CalculateDistance(points[i], points[j]);
            }
        }
    }
}

double DistanceHelper::GetDistanceByPointIndex(const unsigned int& pointIndex1, const unsigned int& pointIndex2){
    return this->distanceMatrix[pointIndex1][pointIndex2];
}
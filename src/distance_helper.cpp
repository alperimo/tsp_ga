#include <math.h>

#include "distance_helper.h"

DistanceHelper::DistanceHelper(){
    // Constructor
}

long double DistanceHelper::ToRadians(const long double& degree){
    return degree * (M_PI / 180.0);
}

long double DistanceHelper::CalculateDistance(const Point& point1, const Point& point2){
    auto point1Lat = ToRadians(point1.GetLatitude()), point1Lon = ToRadians(point1.GetLongitude());
    auto point2Lat = ToRadians(point2.GetLatitude()), point2Lon = ToRadians(point2.GetLongitude());

    // Harvesine formula
    auto dLat = point2Lat - point1Lat;
    auto dLon = point2Lon - point1Lon;

    long double ans = pow(sin(dLat / 2), 2) + cos(point1Lat) * cos(point2Lat) * pow(sin(dLon / 2), 2);
    ans = 2 * asin(sqrt(ans));

    // Distance in kilometers
    auto km = ans * RADIO_TIERRA;
    return km;
}

void DistanceHelper::CreateDistanceMatrixFromPoints(const std::vector<Point>& points) {
    auto totalPoints = points.size();
    
    this->distanceMatrix = std::vector<std::vector<long double>>(totalPoints, std::vector<long double>(totalPoints, 0.0));
    
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

long double DistanceHelper::GetDistanceByPointIndex(const unsigned int& pointIndex1, const unsigned int& pointIndex2){
    return this->distanceMatrix[pointIndex1][pointIndex2];
}
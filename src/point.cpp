#include "point.h"

Point::Point(int id, float latitude, float longitude){
    this->id = id;
    this->latitude = latitude;
    this->longitude = longitude;
}

int Point::GetId() const{
    return this->id;
}

float Point::GetLatitude() const{
    return this->latitude;
}

float Point::GetLongitude() const{
    return this->longitude;
}
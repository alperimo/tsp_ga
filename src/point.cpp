#include "point.h"

Point::Point(int id_, float latitude_, float longitude_) : id(id_), latitude(latitude_), longitude(longitude_)
{
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
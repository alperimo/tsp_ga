#include "point.h"

Point::Point(int id_, long double latitude_, long double longitude_) : id(id_), latitude(latitude_), longitude(longitude_)
{
}

int Point::GetId() const{
    return this->id;
}

long double Point::GetLatitude() const{
    return this->latitude;
}

long double Point::GetLongitude() const{
    return this->longitude;
}
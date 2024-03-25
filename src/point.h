#ifndef POINT_H
#define POINT_H

class Point{
    public:
        Point(int id_, long double latitude_, long double longitude_);

        int GetId() const;
        long double GetLatitude() const;
        long double GetLongitude() const;

    private:
        int id;
        long double latitude;
        long double longitude;
};

#endif
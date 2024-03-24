#ifndef POINT_H
#define POINT_H

class Point{
    public:
        Point(int id, float latitude, float longitude);

        int GetId() const;
        float GetLatitude() const;
        float GetLongitude() const;

    private:
        int id;
        float latitude;
        float longitude;
};

#endif
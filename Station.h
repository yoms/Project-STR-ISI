#ifndef STATION_H
#define STATION_H
#include "Drawable.h"
class Station : public Drawable
{
public:
    enum Type
    {
        Terminus,
        NonTerminus
    };
    Station(Station::Type);
    void draw(QPainter *);
private:
    Type typeStation;
};

#endif // STATION_H

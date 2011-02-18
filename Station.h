#ifndef STATION_H
#define STATION_H
#include "Drawable.h"
class Station : public Drawable
{
    enum Type
    {
        Terminus,
        NonTerminus
    };
    Type typeStation;
public:
    Station(Station::Type);
    void draw(QPainter *);
};

#endif // STATION_H

#ifndef STATION_H
#define STATION_H
#include "Drawable.h"
class Station : public Drawable
{
public:
    Station();
    void draw(QPainter *);
};

#endif // STATION_H

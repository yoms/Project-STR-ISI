#ifndef STATION_H
#define STATION_H
#include "Drawable.h"
#include "Feu.h"
class Station : public Feu
{
public:
    enum Type
    {
        Terminus,
        NonTerminus
    };
    Station(Station::Type);
    void draw(QPainter *);
    bool indiquerPassage();
private:
    Type m_typeStation;
};

#endif // STATION_H

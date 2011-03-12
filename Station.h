#ifndef STATION_H
#define STATION_H
#include "Drawable.h"
#include "FeuStation.h"
class FeuStation;
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
    bool indiquerPassage();
    void addFeuStation(FeuStation*);
private:
    Type m_typeStation;
    FeuStation* m_feuStation;
};

#endif // STATION_H

#ifndef FEUSTATION_H
#define FEUSTATION_H

#include "Feu.h"
#include "Station.h"
class Station;
class FeuStation : public Feu
{
public:
    FeuStation();
    bool indiquerPassage();
    void addStation(Station*);
    void tick(){}
private:
    Station* m_station;
};

#endif // FEUSTATION_H

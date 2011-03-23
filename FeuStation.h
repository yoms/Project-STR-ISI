#ifndef FEUSTATION_H
#define FEUSTATION_H

#include "Feu.h"
#include "Station.h"
class Station;
class FeuStation : public Feu
{
public:
    FeuStation();
    void addStation(Station*);
    void tick(){}
    void newMessage();
    void setEtat(Etat);
private:
    Station* m_station;
    bool m_free;
};

#endif // FEUSTATION_H

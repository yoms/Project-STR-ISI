#ifndef PERSONNE_H
#define PERSONNE_H
#include "Thread.h"
class Station;
class Tram;
class Personne
{
    enum Etat{
        NeedTicket,
        NeedGetOnTheTram,
        NeedGetOffTheTram
    };
    Station *m_station;
    Tram *m_tram;
    Etat m_etat;
public:
    Personne();
    Station* station(){return m_station;}
    void setStation(Station* s){m_station = s;}
    Tram* tram(){return m_tram;}
    void setTram(Tram* t){m_tram = t;}

    void run();
    void buyTicket();
    void punchTicket();
    void getOnTheTram();
    void getOffTheTram();
    void waitInStation();
    void waitInTram();
    void triggerEmergencyStop();
};

#endif // PERSONNE_H

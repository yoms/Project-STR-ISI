#ifndef TRAM_H
#define TRAM_H
#include <QPoint>
#include <QObject>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include "Drawable.h"
#include "ThreadMessage.h"
#include "Timer.h"

#define NB_DOORS 4
#define NB_COMPOSTER 4
#define NB_EMERGENCY_STOP 4
#define CAPACITE 150

class QPainter;
class Trajet;
class Tram : public Drawable, public ThreadMessage, public TimerListener
{
public:
    enum Etat{MARCHE,ARRET,MARCHEAVUE};
    Tram();
    void tick();
    void draw(QPainter *);
    void run();
    void stop();
    void speedUp();
    void slowDown();
    void turnAround();
    void openDoors();
    void closeDoors();
    void setTrajet(Trajet*);
    int vitesse(){return m_vitesse;}
    Tram::Etat etat(){return m_etat;}
    void changeEtat();
private:
    static void _obstacleFunction(int sigNumb, siginfo_t *si, void *uc);
private:
    Timer* m_timer;
    Trajet* m_trajet;
    int m_nbTick;
    int m_vitesse;
    Etat m_etat;
};

#endif // TRAM_H

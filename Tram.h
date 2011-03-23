#ifndef TRAM_H
#define TRAM_H
#include <QPoint>
#include <QObject>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include "Drawable.h"
#include "ThreadMessage.h"
#include "Timer.h"
#include "Obstacle.h"


#define NB_DOORS 4
#define NB_COMPOSTER 4
#define NB_EMERGENCY_STOP 4
#define CAPACITE 150

class QPainter;
class Trajet;
class Tram : public Drawable, public ThreadMessage, public TimerListener
{
public:
    enum Etat{
        Acceleration,
        Desceleration,
        Marche,
        Arret,
        MarcheAVue};
    Tram();
    virtual ~Tram(){}
    void tick();
    void draw(QPainter *);
    void run();
    void detectionObstacle();
    void avancer();
    void stop();
    void speedUp();
    void slowDown();
    void turnAround();
    void openDoors();
    void closeDoors();
    void setTrajet(Trajet*);
    int vitesse(){return m_vitesse;}
    Tram::Etat etat(){return m_etat;}
    virtual QString className(){ return QString("Tram");}
private:
    void newMessage();
private:
    Trajet* m_trajet;
    int m_nbTick;
    int m_vitesse;
    pthread_mutex_t m_mutex;
    Etat m_etat;
    Obstacle* m_obstacle;
};

#endif // TRAM_H

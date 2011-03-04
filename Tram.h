#ifndef TRAM_H
#define TRAM_H
#include <QPoint>
#include <QObject>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include "Drawable.h"
#include "Thread.h"
#include "Stepable.h"

#define NB_DOORS 4
#define NB_COMPOSTER 4
#define NB_EMERGENCY_STOP 4
#define CAPACITE 150

class QPainter;
class Trajet;
class Tram : public Drawable, public Stepable
{
    Trajet* m_trajet;
public:
    Tram();
    void draw(QPainter *);
    void run();
    void stop();
    void speedUp();
    void slowDown();
    void turnAround();
    void openDoors();
    void closeDoors();
    void setTrajet(Trajet*);
    virtual void nextStep();
};

#endif // TRAM_H

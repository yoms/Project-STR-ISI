#ifndef TRAM_H
#define TRAM_H
#include <QPoint>
#include <QObject>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include "Drawable.h"
#include "Thread.h"
#include "Stepable.h"
class QPainter;
class Trajet;
class Tram : public Drawable, public Stepable
{
    Trajet* m_trajet;
public:
    Tram();
    void draw(QPainter *);
    void run();
    void setTrajet(Trajet*);
    virtual void nextStep();
};

#endif // TRAM_H

#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <QPoint>
#include "ThreadMessage.h"
#include "Drawable.h"
#include "Timer.h"

class Obstacle : public Drawable, public ThreadMessage, public TimerListener
{
    QPoint m_lieu;
public:
    Obstacle();
    virtual bool indiquerPassage() = 0;
    QPoint lieu(){return m_lieu;}
    void setLieu(QPoint l){m_lieu = l;}
    virtual QString className(){ return QString("Obstacle");}
private:
    static void _obstacleFunction(int sigNumb, siginfo_t *si, void *uc);

};

#endif // OBSTACLE_H

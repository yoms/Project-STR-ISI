#ifndef FEU_H
#define FEU_H

#include "Obstacle.h"
#include "Drawable.h"
#include "Thread.h"
#include "Timer.h"
class Feu : public Obstacle, public Thread, public TimerListener
{
public:
    Feu();
    bool indiquerPassage();
    void draw(QPainter *);
    void run();
    void tick();

    enum Etat {
        PASSAGE = 0,
        ARRET,
    };

private:
    void setEtat(Etat);
    Etat m_etat;
    Timer* m_timer;
};

#endif // FEU_H

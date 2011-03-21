#ifndef FEU_H
#define FEU_H

#include "Obstacle.h"
#include "Drawable.h"
#include "Timer.h"
class Feu : public Obstacle, public TimerListener
{
public:

    enum Etat {
        PASSAGE = 0,
        ARRET,
    };
    Feu();
    bool indiquerPassage();
    void draw(QPainter *);
    void run();
    void tick();
    Feu::Etat etat();

protected:
    void setEtat(Etat);
    Etat m_etat;
    Timer* m_timer;
};

#endif // FEU_H

#ifndef FEU_H
#define FEU_H

#include "Obstacle.h"
#include "Drawable.h"
#include "Timer.h"
class Feu : public Obstacle
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
    Feu::Etat etat();
    virtual QString className(){ return QString("Feu");}

protected:
    void setEtat(Etat);
    Etat m_etat;
};

#endif // FEU_H

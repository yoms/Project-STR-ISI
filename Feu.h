#ifndef FEU_H
#define FEU_H

#include "Obstacle.h"
class Feu : public Obstacle
{
public:
    Feu();
    bool indiquerPassage();

    enum Etat {
        PASSAGE = 0,
        ARRET,
    };

    void setEtat(Etat);
private:
    Etat m_etat;
};

#endif // FEU_H

#include "Feu.h"

Feu::Feu()
{
}

bool Feu::indiquerPassage() {
    return this->m_etat ;
}


void Feu::setEtat(Feu::Etat etat) {
    this->m_etat = etat;
}

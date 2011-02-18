#include "Porte.h"

Porte::Porte()
{
}

void Porte::ouvrir() {
    this->m_etat = Porte::OUVERT;
}

void Porte::fermer() {
    this->m_etat = Porte::FERME;
}

Porte::Etat Porte::etat(){
    return this->m_etat;
}

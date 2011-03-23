#include "Composteur.h"
#include <QDebug>

extern "C" {
    extern void adaPunchTicket (int);
    extern void adaCreateComposteur(int);
}

Composteur::Composteur()
{
    adaCreateComposteur(0);
}

void Composteur::punchTicket()
{
    adaPunchTicket(0);
}

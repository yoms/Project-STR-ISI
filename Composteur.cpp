#include "Composteur.h"
#include <QDebug>

extern "C" {
    extern void adaPunchTicket (int);
    extern void adaCreateComposteur(int);
}

int Composteur::globalId = 0;

// TODO créer un destructeur qui appelle une fonction adaDeleteComposteur

Composteur::Composteur() : ThreadMessage()
{
    globalId ++;
    this->id = globalId;
    adaCreateComposteur(this->id);
}

void Composteur::run() {}

void Composteur::newMessage()
{

}

void Composteur::punchTicket()
{
    adaPunchTicket(this->id);
}

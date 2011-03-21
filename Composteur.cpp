#include "Composteur.h"

extern "C" {
    extern void adaPunchTicket (void);
}

Composteur::Composteur()
{
}

void Composteur::punchTicket()
{
    adaPunchTicket();
}

#include "BorneAchat.h"
#include <QDebug>

extern "C" {
    extern bool adaGiveTicket (void);
}

BorneAchat::BorneAchat()
{}

bool BorneAchat::giveTicket() {
    adaGiveTicket();
}


#ifndef COMPOSTEUR_H
#define COMPOSTEUR_H

#include "ThreadMessage.h"

class Composteur : public ThreadMessage
{
public:
    Composteur();
    void run();
    void punchTicket();
    int id;
private:
    void newMessage();
    static int globalId;
};

#endif // COMPOSTEUR_H

#ifndef CHAUFFEUR_H
#define CHAUFFEUR_H

#define VISION_FIELD 2

class Chauffeur
{
public:
    Chauffeur();
    void run();
    void stop();
    void speedUp();
    void slowDown();
    void turnAround();
    void openDoors();
    void closeDoors();
};

#endif // CHAUFFEUR_H

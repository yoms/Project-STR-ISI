#ifndef TRACTION_H
#define TRACTION_H

#define SPEED 100

class Traction
{
public:
    Traction();
    void run();
    void stop();
    void speedUp();
    void slowDown();
    void inverseTraction();
    void emergencyStop();
};

#endif // TRACTION_H

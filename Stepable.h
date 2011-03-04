#ifndef STEPABLE_H
#define STEPABLE_H

class Stepable
{
public:
    Stepable();
    virtual void nextStep() = 0;
};

#endif // STEPABLE_H

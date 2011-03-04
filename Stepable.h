#ifndef STEPABLE_H
#define STEPABLE_H
#include "Thread.h"
class Stepable : public Thread
{
public:
    Stepable();
    virtual void nextStep() = 0;
};

#endif // STEPABLE_H

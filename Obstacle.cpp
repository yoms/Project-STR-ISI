#include "Obstacle.h"
#include <QDebug>

Obstacle::Obstacle():ThreadMessage()
{

    sigemptyset(&this->m_signalAction.sa_mask);
    this->m_signalAction.sa_flags = SA_SIGINFO;
    this->m_signalAction.sa_sigaction = Obstacle::_obstacleFunction;

    if (sigaction(SIGUSR1, &this->m_signalAction, NULL))
    {
        qDebug() << "impossible de creer le handle";
    }
}

void Obstacle::_obstacleFunction(int sigNumb, siginfo_t *si, void *uc) {
    qDebug()<<"Tram passé";
    Obstacle * ptrObs = reinterpret_cast<Obstacle *> (si->si_value.sival_ptr);
    ptrObs->removeMessage();
}

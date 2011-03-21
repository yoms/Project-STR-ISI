#include "Tram.h"
#include "Trajet.h"
#include "Message.h"

#include <QPainter>
#include <QDebug>
#define SIZE 3
#define SIZE_TRAM 4
#define VITESSE_MIN 40
#define VITESSE_MAX 5
#define ACCELERATION 3
#include <pthread.h>
#include <signal.h>
#include <time.h>

Tram::Tram():Drawable(),ThreadMessage()
{
    m_etat = Tram::MARCHE;
    m_nbTick = 0;
    m_vitesse = VITESSE_MIN;
    pthread_mutex_init(&m_mutex,NULL);
    sigemptyset(&this->m_signalAction.sa_mask);
    this->m_signalAction.sa_flags = SA_SIGINFO;
    this->m_signalAction.sa_sigaction = Tram::_obstacleFunction;


    if (sigaction(SIGUSR1, &this->m_signalAction, NULL))
    {
        qDebug() << "impossible de creer le handle";
    }

}
void Tram::run()
{
    for(;;)
    {
        pthread_mutex_lock(&m_mutex);
        if(m_nbTick == m_vitesse-1)
        {
            this->m_nbTick = ++m_nbTick%m_vitesse;
            qDebug() << "Etat du tram avant switch : " << m_etat << " | etat Arret : " << Tram::ARRET;
            switch(m_etat)
            {
            case Tram::MARCHE:
                {
                    Obstacle* o;
                    if((o = m_trajet->obstacleExist(this->m_coordonnee)) == NULL)
                    {
                        if(this->m_trajet->next(this->m_coordonnee) == m_coordonnee)
                            this->m_trajet = this->m_trajet->retour();
                        this->m_coordonnee = this->m_trajet->next(this->m_coordonnee);
                        speedUp();

                    }
                    else
                    {
                        qDebug()<<"Obstacle "<<o->nom();
                        if(!m_obstacles.contains(o)) {
                            isCrossed();
                            Message * m = new Message (this, Message::Passage);
                            o->addMessage(m);
                            this->m_obstacles.append(o);
                        }
                        this->m_coordonnee = this->m_trajet->next(this->m_coordonnee);
//                        if(!o->indiquerPassage())
//                        {
//                            if(o->lieu() == this->m_trajet->next(this->m_coordonnee))
//                                m_etat = Tram::ARRET;
//                            this->m_coordonnee = this->m_trajet->next(this->m_coordonnee);
//                            slowDown();
//                        }
//                        else
//                        {
//                            this->m_coordonnee = this->m_trajet->next(this->m_coordonnee);
//                        }
                    }
                }
                break;
            case Tram::ARRET:
                {
                    m_vitesse = VITESSE_MIN;
                    Obstacle* o;
                    if((o = m_trajet->obstacleExist(this->m_coordonnee)) == NULL)
                    {
                        qDebug() << "Arret pas d'obstacle, en avant MARCHE!";
                    }
                    else
                    {
                        qDebug() << "Arret un obstacle, indiquer passage!";
                        slowDown();
                    }
                }
                break;
            }
        }
    }
}
void Tram::setTrajet(Trajet *t)
{
    this->m_trajet=t;
    this->m_coordonnee = this->m_trajet->trajet().first();
}

void Tram::tick()
{
   this->m_nbTick = ++m_nbTick%m_vitesse;
   pthread_mutex_unlock(&m_mutex);
}

void Tram::draw(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::red);
    painter->setBrush(QBrush(Qt::red));
    QPoint buff = this->m_coordonnee;
    for(int i = 0; i < SIZE; i++)
    {
        drawElemScen(painter, buff.x(), buff.y(), SIZE_TRAM);
        buff = this->m_trajet->previous(buff);
    }

    painter->setPen(Qt::darkGray);
    painter->setBrush(QBrush(Qt::darkGray));
    painter->restore();
}

void Tram::stop()
{

}

void Tram::speedUp()
{
    qDebug() << "SpeedUp : " << m_vitesse;
    m_vitesse = m_vitesse > VITESSE_MAX ? m_vitesse - ACCELERATION : m_vitesse;
}

void Tram::slowDown()
{
    qDebug() << "SlowDown : " << m_vitesse;
    m_vitesse = m_vitesse < VITESSE_MIN ? m_vitesse + ACCELERATION : m_vitesse;
}

void Tram::turnAround()
{

}

void Tram::openDoors()
{

}

void Tram::closeDoors()
{

}

void Tram::changeEtat(){
    qDebug()<<"changeEtat : "<<m_etat;
    switch(m_etat)
    {
    case Tram::MARCHE:
        {
            m_etat = Tram::ARRET;
            slowDown();
        }
        break;
    }
    qDebug()<<"changeEtat : "<<m_etat;
}

void Tram::_obstacleFunction(int sigNumb, siginfo_t *si, void *uc)
{
    Tram * ptrTram = reinterpret_cast<Tram *> (si->si_value.sival_ptr);
    qDebug()<<"Handle tram ";
    ptrTram->changeEtat();
}

void Tram::isCrossed() {
    if(!m_obstacles.isEmpty()){
        qDebug()<<"isCrossed";
        pthread_kill(m_obstacles.first()->threadid(), SIGUSR1);
        m_obstacles.removeFirst();
    }
}

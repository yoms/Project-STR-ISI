#include "Tram.h"
#include "Trajet.h"
#include "Message.h"
#include "Composteur.h"

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
    m_etat = Tram::Acceleration;
    m_nbTick = 0;
    m_vitesse = VITESSE_MIN;
    pthread_mutex_init(&m_mutex,NULL);
    m_composteurList.append(new Composteur); // TODO penser à détruire
}
void Tram::run()
{
    for(;;)
    {
        pthread_mutex_lock(&m_mutex);
        detectionObstacle();
        if(m_nbTick == m_vitesse-1)
        {
            this->m_nbTick = ++m_nbTick%m_vitesse;
            switch(m_etat)
            {
            case Tram::Acceleration:
                {
                    speedUp();
                    avancer();
                }
                break;
            case Tram::Desceleration:
                {
                    slowDown();
                    if(m_obstacle->lieu() == m_trajet->next(m_coordonnee))
                        m_etat = Tram::Arret;
                    else
                        avancer();
                }
                break;
            case Tram::Marche:
                {
                    avancer();
                }
                break;
            case Tram::Arret:
                {
                    m_vitesse = VITESSE_MIN;
                }
                break;

            }
        }
    }
}
void Tram::detectionObstacle()
{
    Obstacle* o;
    if((o = m_trajet->obstacleExist(this->m_coordonnee)) != NULL)
    {
        m_obstacle = o;
        m_obstacle->addMessage(new Message(this,Message::Demande));
    }
    else if(m_obstacle != NULL)
    {
        qDebug() << m_obstacle->nom();
        m_obstacle->addMessage(new Message(this,Message::EstPasse));
        m_obstacle = NULL;
    }

}

void Tram::avancer()
{
    if(this->m_trajet->next(this->m_coordonnee) == m_coordonnee)
                                this->m_trajet = this->m_trajet->retour();
    this->m_coordonnee = this->m_trajet->next(this->m_coordonnee);
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
    if(m_vitesse < VITESSE_MAX)
        m_etat = Tram::Marche;
    else
        m_vitesse -= ACCELERATION;
}

void Tram::slowDown()
{
    if(m_vitesse > VITESSE_MIN)
        m_etat = Tram::Arret;
    else
        m_vitesse += ACCELERATION;
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
void Tram::newMessage()
{
    if(!m_messageList.isEmpty())
    {
        Message *m = m_messageList.takeFirst();
        switch(m->type())
        {
        case Message::Arret:
            {
                m_etat = Tram::Desceleration;
            }
            break;
        case Message::Passage:
            {
                m_etat = Tram::Acceleration;
            }
            break;
        }
    }
}


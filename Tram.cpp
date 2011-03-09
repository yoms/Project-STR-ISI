#include "Tram.h"
#include "Trajet.h"

#include <QPainter>
#include <QDebug>
#define SIZE 3
#define SIZE_TRAM 4
#define VITESSE_MAX 0


Tram::Tram():Drawable(),Thread()
{
    m_timer = new Timer(0,20);
    m_timer->addListener(this);
    m_timer->start();
    m_etat = Tram::MARCHE;

}
void Tram::run()
{
    forever;
}
void Tram::setTrajet(Trajet *t)
{
    this->m_trajet=t;
    this->m_coordonnee = this->m_trajet->trajet().first();
}

void Tram::tick()
{
    switch(m_etat)
    {
    case Tram::MARCHE:
        {
            Obstacle* o;
            if((o = m_trajet->obstacleExist(this->m_coordonnee)) == NULL)
            {
                this->m_coordonnee = this->m_trajet->next(this->m_coordonnee);
            }
            else
            {
                if(!o->indiquerPassage())
                {
                    m_etat = Tram::ARRET;
                }
                else
                {
                    this->m_coordonnee = this->m_trajet->next(this->m_coordonnee);
                }
            }
        }
        break;
    case Tram::ARRET:
        {
            Obstacle* o;
            if((o = m_trajet->obstacleExist(this->m_coordonnee)) == NULL)
            {
                qDebug() << "Arret pas d'obstacle, en avant MARCHE!";
                m_etat = Tram::MARCHE;
            }
            else
            {
                qDebug() << "Arret un obstacle, indiquer passage!";
                m_etat = o->indiquerPassage() ? Tram::MARCHE : Tram::ARRET;
            }
        }
        break;
    }
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

}

void Tram::slowDown()
{

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

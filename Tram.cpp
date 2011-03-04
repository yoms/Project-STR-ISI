#include "Tram.h"
#include "Trajet.h"

#include <QPainter>
#include <QDebug>
#define SIZE 3
#define SIZE_TRAM 4


Tram::Tram():Drawable(),Thread(),Stepable()
{

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

void Tram::nextStep()
{
    this->m_coordonnee = this->m_trajet->next(this->m_coordonnee);
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

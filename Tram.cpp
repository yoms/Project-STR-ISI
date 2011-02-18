#include "Tram.h"
#include <QPainter>
#include <QDebug>
#define SIZE 3
#define SIZE_TRAM 4

Tram::Tram(QTimer *timer, QObject *parent):Drawable(),QThread(parent),m_timer(timer)
{
    connect(this->m_timer, SIGNAL(timeout()), this, SLOT(nextRound()));
}
void Tram::run()
{

    forever;
}
void Tram::nextRound()
{
    m_coordonnee += QPoint(1,1);
}

void Tram::draw(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::red);
    painter->setBrush(QBrush(Qt::red));

    drawElemScen(painter, m_coordonnee.x(), m_coordonnee.y(), SIZE_TRAM);
    painter->setPen(Qt::darkGray);
    painter->setBrush(QBrush(Qt::darkGray));
    painter->restore();
}

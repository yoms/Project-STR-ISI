#include "Tram.h"
#include <QPainter>
#include <QDebug>
#define SIZE 3

Tram::Tram(QTimer *timer, QObject *parent):Drawable(),QThread(parent),m_timer(timer),coor(1,1)
{
    connect(this->m_timer, SIGNAL(timeout()), this, SLOT(nextRound()));
}
void Tram::run()
{

    forever;
}
void Tram::nextRound()
{
    coor += QPoint(1,1);
}

void Tram::setCoor(QPoint p){coor = p;}
void Tram::draw(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::red);
    painter->setBrush(QBrush(Qt::red));

    drawElemScen(painter, coor.x(), coor.y());
    painter->setPen(Qt::darkGray);
    painter->setBrush(QBrush(Qt::darkGray));
    painter->restore();
}

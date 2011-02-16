#ifndef TRAM_H
#define TRAM_H
#include <QThread>
#include <QPoint>
#include <QObject>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include "Drawable.h"
class QPainter;
class Tram : public QThread, public Drawable
{
Q_OBJECT
QPoint coor;
QTimer* m_timer;
public:
    Tram(QTimer * timer, QObject * parent = 0);
    void setCoor(QPoint);
    void draw(QPainter *);
    void run();
public slots:
    void nextRound();
};

#endif // TRAM_H

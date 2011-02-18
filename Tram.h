#ifndef TRAM_H
#define TRAM_H
#include <QThread>
#include <QPoint>
#include <QObject>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include "Drawable.h"
class QPainter;
class Trajet;
class Tram : public QThread, public Drawable
{
Q_OBJECT
    QTimer* m_timer;
    Trajet* m_trajet;
public:
    Tram(QTimer * timer, QObject * parent = 0);
    void draw(QPainter *);
    void run();
    void setTrajet(Trajet*);
public slots:
    void nextRound();
};

#endif // TRAM_H

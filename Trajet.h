#ifndef TRAJET_H
#define TRAJET_H
#include "Drawable.h"
#include <QList>
#include <QPoint>
class Trajet : public Drawable
{
    QList<QPoint> m_trajet;
public:
    Trajet();
    void draw(QPainter *);
    QList<QPoint> trajet();
    void setTrajet(QList<QPoint> &);
    QPoint next(QPoint&);
    QPoint previous(QPoint&);
};

#endif // TRAJET_H

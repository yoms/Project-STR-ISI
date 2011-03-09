#ifndef TRAJET_H
#define TRAJET_H
#include "Drawable.h"
#include <QList>
#include <QPoint>
#include "Obstacle.h"
class Trajet : public Drawable
{
    QList<QPoint> m_trajet;
    QList<Obstacle*> m_obstacle;
public:
    Trajet();
    void draw(QPainter *);
    QList<QPoint> trajet();
    void setTrajet(QList<QPoint> &);
    Obstacle* obstacleExist(QPoint);
    QPoint next(QPoint&);
    QPoint previous(QPoint&);
    void setObstacle(QList<Obstacle*>);
    void addObstacle(Obstacle*);
};

#endif // TRAJET_H

#ifndef TRAJET_H
#define TRAJET_H
#include "Drawable.h"
#include <QList>
#include <QPoint>
#include "Obstacle.h"
#define DISTANCE_VISION 10
class Trajet : public Drawable
{
    QList<QPoint> m_trajet;
    QList<Obstacle*> m_obstacle;
    Trajet* m_trajetRetour;
    pthread_mutex_t m_mutex;
public:
    Trajet();
    ~Trajet(){}
    void setRetour(Trajet* t){m_trajetRetour = t;}
    Trajet* retour(){return m_trajetRetour;}
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

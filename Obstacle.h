#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <QPoint>
class Obstacle
{
    QPoint m_lieu;
public:
    Obstacle();
    virtual bool indiquerPassage() = 0;
    QPoint lieu(){return m_lieu;}
    void setLieu(QPoint l){m_lieu = l;}
};

#endif // OBSTACLE_H

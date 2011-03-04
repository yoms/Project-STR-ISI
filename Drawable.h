#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <QPoint>
class QPainter;
class Drawable
{
protected:
    QPoint m_coordonnee;
public:
    Drawable();
    virtual void draw(QPainter*) = 0;
    void drawElemScen(QPainter*, int, int, int);

    QPoint coordonnee(){return m_coordonnee;}
    void setCoordonnee(QPoint p){m_coordonnee = p;}
};

#endif // DRAWABLE_H

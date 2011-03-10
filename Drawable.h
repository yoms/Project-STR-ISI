#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <QPoint>
#include <QString>
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
    QString nom(){return m_nom;}
    void setNom(QString n){m_nom = n;}
private:
    QString m_nom;
};

#endif // DRAWABLE_H

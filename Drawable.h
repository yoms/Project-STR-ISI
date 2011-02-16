#ifndef DRAWABLE_H
#define DRAWABLE_H
class QPainter;
class Drawable
{
public:
    Drawable();
    virtual void draw(QPainter*) = 0;
    void drawElemScen(QPainter*, int, int);
};

#endif // DRAWABLE_H

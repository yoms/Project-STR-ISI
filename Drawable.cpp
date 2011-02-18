#include "Drawable.h"
#include <QRect>
#include <QPainter>
#define SIZEX 0
Drawable::Drawable()
{
}
void Drawable::drawElemScen(QPainter *painter, int X, int Y, int size)
{
        QRectF rect(SIZEX,SIZEX,size,size);
        rect.moveCenter(rect.center() + QPointF(X, Y));
        painter->drawRect(rect);
}

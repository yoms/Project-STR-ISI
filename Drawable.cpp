#include "Drawable.h"
#include <QRect>
#include <QPainter>
#define SIZEX 0
#define SIZEY 2
Drawable::Drawable()
{
}
void Drawable::drawElemScen(QPainter *painter, int X, int Y)
{
        QRectF rect(SIZEX,SIZEX,SIZEY,SIZEY);
        rect.moveCenter(rect.center() + QPointF(12*X, 12*Y));
        painter->drawRect(rect);
}

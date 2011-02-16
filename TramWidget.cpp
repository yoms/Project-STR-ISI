#include "TramWidget.h"
#include "Tram.h"
#include <QtGui/QPaintEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QPainter>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include <QDebug>

TramWidget::TramWidget(QWidget *parent)
   :QWidget(parent), pixmap(1000,600) {

        setFocusPolicy(Qt::StrongFocus);
        qsrand(QTime::currentTime().second());

        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));

        pixmap.fill(Qt::black);
        itemList << new Tram(timer,this);
        itemList << new Tram(timer,this);
        ((Tram*)itemList[1])->setCoor(QPoint(5,5));
        foreach(Drawable* t, itemList)
        {
            QTimer::singleShot(0,(Tram*)t,SLOT(start()));
        }

        timer->start(300);
}

TramWidget::~TramWidget() {
}
void TramWidget::paintEvent(QPaintEvent *event)
{
    qDebug() << "paintEvent";
        QPainter painter(this);
        pixmap.fill(Qt::black);
        painter.drawPixmap(0,0,pixmap);

        foreach(Drawable* d, itemList)
        {
            d->draw(&painter);
        }
}


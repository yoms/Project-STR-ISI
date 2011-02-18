#include "TramWidget.h"
#include "Tram.h"
#include "Station.h"
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
        Station* s = new Station;
        qDebug() << "station";
        QPoint p2(10,10);
        s->setCoordonnee(p2);
        itemList << new Tram(timer,this);
        itemList << s;
        QPoint p(5,5);

        ((Tram*)itemList[0])->setCoordonnee(p);
        QTimer::singleShot(0,((Tram*)itemList[0]),SLOT(start()));

        timer->start(300);
}

TramWidget::~TramWidget() {
}
void TramWidget::paintEvent(QPaintEvent *event)
{
    qDebug() << "paintEvent";
        QPainter painter(this);
        pixmap.fill(Qt::white);
        painter.drawPixmap(0,0,pixmap);

        foreach(Drawable* d, itemList)
        {
            d->draw(&painter);
        }
}


#include "TramWidget.h"
#include "Tram.h"
#include "Station.h"
#include "Trajet.h"
#include <QtGui/QPaintEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QPainter>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include <QDebug>

TramWidget::TramWidget(QWidget *parent)
   :QWidget(parent), m_pixmap(1000,600) {

        setFocusPolicy(Qt::StrongFocus);
        qsrand(QTime::currentTime().second());

        m_timer = new QTimer(this);
        connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));

        setupTrajet();

        Tram * tram = new Tram(m_timer,this);
        m_itemList << tram;

        tram->setTrajet(m_trajetList[0]);

        QTimer::singleShot(0,(tram),SLOT(start()));

        m_timer->start(300);
}
void TramWidget::setupTrajet()
{
    QList<QPoint> tra;

    for(int i = 0; i < 130; i++)
            tra << QPoint(i,25);

    Trajet* traj = new Trajet;
    traj->setTrajet(tra);
    m_trajetList << traj;
    foreach(Trajet* t , m_trajetList)
        m_itemList << t;

}

TramWidget::~TramWidget() {
}
void TramWidget::paintEvent(QPaintEvent *event)
{
        QPainter painter(this);
        m_pixmap.fill(Qt::white);
        painter.drawPixmap(0,0,m_pixmap);

        foreach(Drawable* d, m_itemList)
        {
            d->draw(&painter);
        }
}


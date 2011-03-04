#include "TramWidget.h"
#include "Tram.h"
#include "Station.h"
#include "Trajet.h"
#include <math.h>
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
        connect(m_timer, SIGNAL(timeout()), this, SLOT(nextStep()));

        setupTrajet();

        Tram * tram = new Tram;
        m_drawableList << tram;
        m_stepableList << tram;

        tram->setTrajet(m_trajetList[0]);
        tram->start();

        m_timer->start(50);
}
void TramWidget::nextStep()
{
    foreach(Stepable* d, m_stepableList)
    {
        d->nextStep();
    }
}

void TramWidget::setupTrajet()
{
    QList<QPoint> tra;
    QPoint last;

    for(int i = 25; i < 155; i++)
            tra << QPoint(i,25);

    last = tra.last();
    for(double i = 3; i > 0; i -= 0.10)
            tra << QPoint(last.x()+25*sin(i), last.y()+25+25*cos(i));

    last = tra.last();
    for(double i = 3; i < 6; i += 0.10)
            tra << QPoint(last.x()+25*sin(i), last.y()+25+25*cos(i));

    last = tra.last();
    for(int i = 1; i < 155; i++)
            tra << QPoint(last.x()+i,last.y());

    last = tra.last();
    for(double i = 3; i > 1.3; i -= 0.10)
            tra << QPoint(last.x()+25*sin(i), last.y()+25+25*cos(i));

    Trajet* traj = new Trajet;
    traj->setTrajet(tra);
    m_trajetList << traj;
    foreach(Trajet* t , m_trajetList)
        m_drawableList << t;

}

TramWidget::~TramWidget() {
}
void TramWidget::paintEvent(QPaintEvent *event)
{
        QPainter painter(this);
        m_pixmap.fill(Qt::white);
        painter.drawPixmap(0,0,m_pixmap);

        foreach(Drawable* d, m_drawableList)
        {
            d->draw(&painter);
        }
}


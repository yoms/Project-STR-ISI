#include "TramWidget.h"
#include "Tram.h"
#include "Station.h"
#include "Feu.h"
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

        m_timer->start(50);

        setupTrajet();

        Tram * tram = new Tram;
        m_drawableList << tram;
        tram->setTrajet(m_trajetList[0]);
        tram->start();

}

void TramWidget::setupTrajet()
{
    QList<QPoint> tra;
    QPoint last;
    double radius = 0.05;
    Station* s1 = new Station(Station::Terminus);
    s1->setCoordonnee(QPoint(25,30));
    m_drawableList << s1;

    for(int i = 25; i < 155; i++)
            tra << QPoint(i,25);

    last = tra.last();
    for(double i = 3; i > 0; i -= radius)
            tra << QPoint(last.x()+25*sin(i), last.y()+25+25*cos(i));

    last = tra.last();

    Feu* feu = new Feu;
    feu->setCoordonnee(tra.last()+QPoint(0,3));
    m_drawableList << feu;
    feu->setLieu(last);
    feu->start();

    for(double i = 3; i < 6; i += radius)
            tra << QPoint(last.x()+25*sin(i), last.y()+25+25*cos(i));

    last = tra.last();
    for(int i = 1; i < 155; i++)
            tra << QPoint(last.x()+i,last.y());

    last = tra.last();
    for(double i = 3; i > 1.3; i -= radius)
            tra << QPoint(last.x()+25*sin(i), last.y()+25+25*cos(i));


    last = tra.last();
    Station* s2 = new Station(Station::Terminus);
    s2->setCoordonnee(last+QPoint(5,-3));
    m_drawableList << s2;

    Trajet* traj = new Trajet;
    traj->setTrajet(tra);
    m_trajetList << traj;
    traj->addObstacle(feu);
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


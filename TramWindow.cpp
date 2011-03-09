#include "TramWindow.h"
#include "ui_tramwindow.h"
#include "TramPropertiesWidget.h"
#include "Tram.h"
#include "Station.h"
#include "Feu.h"
#include "Trajet.h"
#include "TramPropertiesWidget.h"
#include "ObstacleWidget.h"
#include <math.h>

TramWindow::TramWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TramWindow)
{
    ui->setupUi(this);

    setupTrajet();
    Tram * tram = new Tram;
    m_tramList << tram;
    tram->setTrajet(m_trajetList[0]);
    tram->start();
    setupDrawingWidget();

}
void TramWindow::setupDrawingWidget()
{
    QList<Drawable*> d;

    for(int i = 0; i < m_obstacleList.size(); i++)
    {
        d << m_obstacleList[i];
        ObstacleWidget* obstacleW = new ObstacleWidget(m_obstacleList[i]);
        ui->m_propertiesLayout->addWidget(obstacleW);
    }
    for(int i = 0; i < m_stationList.size(); i++)
        d << m_stationList[i];
    for(int i = 0; i < m_trajetList.size(); i++)
        d << m_trajetList[i];
    for(int i = 0; i < m_tramList.size(); i++)
    {
        d << m_tramList[i];
        TramPropertiesWidget* tramPW = new TramPropertiesWidget(m_tramList[i]);
        ui->m_propertiesLayout->addWidget(tramPW);
    }
    ui->widget->setDrawableList(d);
}

void TramWindow::setupTrajet()
{
    QList<QPoint> tra;
    QPoint last;
    double radius = 0.05;
    Station* s1 = new Station(Station::Terminus);
    s1->setCoordonnee(QPoint(25,30));
    m_stationList << s1;

    for(int i = 25; i < 155; i++)
            tra << QPoint(i,25);

    last = tra.last();
    for(double i = 3; i > 0; i -= radius)
            tra << QPoint(last.x()+25*sin(i), last.y()+25+25*cos(i));

    last = tra.last();

    Feu* feu = new Feu;
    feu->setCoordonnee(tra.last()+QPoint(0,3));
    m_obstacleList << feu;
    feu->setLieu(last);
    feu->start();

    for(double i = 3; i < 6; i += radius)
            tra << QPoint(last.x()+25*sin(i), last.y()+25+25*cos(i));

    last = tra.last();

    Feu* feu2 = new Feu;
    feu2->setCoordonnee(tra.last()+QPoint(0,3));
    m_obstacleList << feu2;
    feu2->setLieu(last);
    feu2->start();

    for(int i = 1; i < 155; i++)
            tra << QPoint(last.x()+i,last.y());

    last = tra.last();
    for(double i = 3; i > 1.3; i -= radius)
            tra << QPoint(last.x()+25*sin(i), last.y()+25+25*cos(i));


    last = tra.last();
    Station* s2 = new Station(Station::Terminus);
    s2->setCoordonnee(last+QPoint(5,-3));
    m_stationList << s2;

    Trajet* traj = new Trajet;
    traj->setTrajet(tra);
    m_trajetList << traj;

    foreach(Obstacle* o, m_obstacleList)
        traj->addObstacle(o);

    foreach(Trajet* t , m_trajetList)
        m_trajetList << t;

}
TramWindow::~TramWindow()
{
    delete ui;
}

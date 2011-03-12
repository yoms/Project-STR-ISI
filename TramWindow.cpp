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
    Tram * tram2 = new Tram;
    m_tramList << tram2;
    tram2->setTrajet(m_trajetList[1]);
    tram2->start();
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
//    for(int i = 0; i < m_stationList.size(); i++)
//        d << m_stationList[i];
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
    QPoint last(25,25);
    double radius = 0.05;


    Station* s1 = new Station(Station::NonTerminus);
        s1->setCoordonnee(last + QPoint(0,5));
        s1->setLieu(last);
        s1->setNom("haut gauche");
        m_obstacleList << s1;

    for(double i = 0; i < 50; i++)
        tra << QPoint(last.x()+i, last.y());

    last = tra.last();
    for(double i = 3; i > 1.5; i -= radius)
            tra << QPoint(last.x()+25*sin(i), last.y()+25+25*cos(i));

    last = tra.last();
    for(double i = 1; i < 50; i++)
            tra << QPoint(last.x(), last.y()+i);

    last = tra.last();
    for(double i = -1.5; i < 0; i += radius)
            tra << QPoint(last.x()+25+25*sin(i), last.y()+25*cos(i));

    last = tra.last();
    for(double i = 1; i < 75; i++)
        tra << QPoint(last.x()+i, last.y());


    last = tra.last();
    for(double i = 0; i < 1.5; i += radius)
            tra << QPoint(last.x()+1+25*sin(i), last.y()-25+25*cos(i));

    last = tra.last();
    for(double i = 1; i < 50; i++)
        tra << QPoint(last.x(), last.y()-i);

    last = tra.last();
    for(double i = 4.5; i > 3; i -= radius)
            tra << QPoint(last.x()+25+25*sin(i), last.y()+3+25*cos(i));

    last = tra.last();
    for(double i = 1; i < 50; i++)
        tra << QPoint(last.x()+i, last.y());


    last = tra.last();
    Station* s2 = new Station(Station::NonTerminus);
        s2->setCoordonnee(last + QPoint(0,5));
        s2->setLieu(last);
        s2->setNom("haut droite");
        m_obstacleList << s2;

    Trajet* traj = new Trajet;
    traj->setTrajet(tra);
    m_trajetList << traj;
//----------------------------------------------------------------------------------------------------------------------------------
    tra.clear();

    last = QPoint(25,217);

    Station* s3 = new Station(Station::NonTerminus);
        s3->setCoordonnee(last + QPoint(0,5));
        s3->setLieu(last);
        s3->setNom("bas gauche");
        m_obstacleList << s3;

    for(double i = 0; i < 50; i++)
        tra << QPoint(last.x()+i, last.y());

    last = tra.last();
    for(double i = 0; i < 1.5; i += radius)
            tra << QPoint(last.x()+1+25*sin(i), last.y()-25+25*cos(i));

    last = tra.last();
    for(double i = 1; i < 50; i++)
            tra << QPoint(last.x(), last.y()-i);

    last = tra.last();
    for(double i = 4.5; i > 3; i -= radius)
            tra << QPoint(last.x()+25+25*sin(i), last.y()+3+25*cos(i));

    last = tra.last();
    for(double i = 1; i < 75; i++)
        tra << QPoint(last.x()+i, last.y());

    last = tra.last();
    for(double i = 3; i > 1.5; i -= radius)
            tra << QPoint(last.x()+25*sin(i), last.y()+25+25*cos(i));

    last = tra.last();
    for(double i = 1; i < 50; i++)
            tra << QPoint(last.x(), last.y()+i);

    last = tra.last();
    for(double i = -1.5; i < 0; i += radius)
            tra << QPoint(last.x()+25+25*sin(i), last.y()+25*cos(i));

    last = tra.last();
    for(double i = 1; i < 50; i++)
        tra << QPoint(last.x()+i, last.y());


    last = tra.last();
    Station* s4 = new Station(Station::NonTerminus);
        s4->setCoordonnee(last + QPoint(0,5));
        s4->setLieu(last);
        s4->setNom("bas droite");
        m_obstacleList << s4;

    Trajet* traj2 = new Trajet;
    traj2->setTrajet(tra);
    m_trajetList << traj2;



    foreach(Trajet* t , m_trajetList)
        m_trajetList << t;

}
TramWindow::~TramWindow()
{
    delete ui;
}

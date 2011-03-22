#include "TramWindow.h"
#include "ui_tramwindow.h"
#include "TramPropertiesWidget.h"
#include "Tram.h"
#include "Station.h"
#include "Feu.h"
#include "FeuStation.h"
#include "Trajet.h"
#include "TramPropertiesWidget.h"
#include "ObstacleWidget.h"
#include <math.h>
#include <QDebug>

TramWindow::TramWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TramWindow)
{
    m_timer = new Timer(0,20);
    ui->setupUi(this);

    setupTrajet();
    Tram * tram = new Tram;
    m_tramList << tram;
    tram->setTrajet(m_trajetList[0]);
    tram->start();
    Tram * tram2 = new Tram;
    m_tramList << tram2;
    tram2->setTrajet(m_trajetList[2 ]);
    tram2->start();
    setupDrawingWidget();
    for(int i = 0; i < m_tramList.size(); i++)
        m_timer->addListener(m_tramList[i]);
    for(int i = 0; i < m_obstacleList.size(); i++)
        m_timer->addListener(m_obstacleList[i]);

    m_timer->start();

}
TramWindow::~TramWindow()
{
    delete ui;
    delete m_timer;
    for(int i = 0; i < m_obstacleWidgetList.size(); i++)
    {
        delete m_obstacleWidgetList[i];
    }
    for(int i = 0; i < m_tramPropertiesWidgetList.size(); i++)
    {
        delete m_tramPropertiesWidgetList[i];
    }
    for(int i = 0; i < m_stationList.size(); i++)
    {
        delete m_stationList[i];
    }
    for(int i = 0; i < m_obstacleList.size(); i++)
    {
        delete m_obstacleList[i];
    }
    for(int i = 0; i < m_tramList.size(); i++)
    {
        delete m_tramList[i];
    }
    for(int i = 0; i < m_trajetList.size(); i++)
    {
        if(m_trajetList[i] != NULL)
            delete m_trajetList[i];
    }
}

void TramWindow::setupDrawingWidget()
{
    QList<Drawable*> d;

    for(int i = 0; i < m_obstacleList.size(); i++)
    {
        d << m_obstacleList[i];
        m_obstacleWidgetList << new ObstacleWidget(m_obstacleList[i]);
        ui->m_propertiesLayout->addWidget(m_obstacleWidgetList.last());
    }
    for(int i = 0; i < m_stationList.size(); i++)
        d << m_stationList[i];
    for(int i = 0; i < m_trajetList.size(); i++)
        d << m_trajetList[i];
    for(int i = 0; i < m_tramList.size(); i++)
    {
        d << m_tramList[i];
        m_tramPropertiesWidgetList << new TramPropertiesWidget(m_tramList[i]);
        ui->m_propertiesLayout->addWidget(m_tramPropertiesWidgetList.last());
    }
    ui->widget->setDrawableList(d);
}

void TramWindow::setupTrajet()
{
    QList<QPoint> tra, traret;
    QPoint last(25,25);
    double radius = 0.05;
    Station* s1 = new Station(Station::NonTerminus);
        s1->setCoordonnee(last + QPoint(0,5));
        s1->setNom("haut gauche");
        m_stationList << s1;

        FeuStation* feuS1 = new FeuStation;
        feuS1->setCoordonnee(last+QPoint(0,-5));
        m_obstacleList << feuS1;
        feuS1->setLieu(last);
        feuS1->setNom("FeuS1");
        feuS1->addStation(s1);
        s1->addFeuStation(feuS1);
        feuS1->start();





    for(double i = 0; i < 50; i++)
    {
        tra << QPoint(last.x()+i, last.y());
        traret.prepend(tra.last());
    }

    last = tra.last();
    Feu * f1 = new Feu;
    f1->setCoordonnee(last+QPoint(0,-5));
    m_obstacleList << f1;
    f1->setLieu(last);
    f1->setNom("F1");
    f1->setEtat(Feu::ARRET);
    f1->start();

    last = tra.last();
    for(double i = 3; i > 1.5; i -= radius)
    {
            tra << QPoint(last.x()+25*sin(i), last.y()+25+25*cos(i));
            traret.prepend(tra.last());
    }

    last = tra.last();
    for(double i = 1; i < 50; i++)
    {
            tra << QPoint(last.x(), last.y()+i);
            traret.prepend(tra.last());
    }

    last = tra.last();
    for(double i = -1.5; i < 0; i += radius)
    {
            tra << QPoint(last.x()+25+25*sin(i), last.y()+25*cos(i));
            traret.prepend(tra.last());
    }

    last = tra.last();
    for(double i = 1; i < 75; i++)
    {
        tra << QPoint(last.x()+i, last.y());
        traret.prepend(tra.last());
    }


    last = tra.last();
    for(double i = 0; i < 1.5; i += radius)
    {
            tra << QPoint(last.x()+1+25*sin(i), last.y()-25+25*cos(i));
            traret.prepend(tra.last());
    }

    last = tra.last();
    for(double i = 1; i < 50; i++)
    {
        tra << QPoint(last.x(), last.y()-i);
        traret.prepend(tra.last());
    }

    last = tra.last();
    for(double i = 4.5; i > 3; i -= radius)
    {
            tra << QPoint(last.x()+25+25*sin(i), last.y()+3+25*cos(i));
            traret.prepend(tra.last());
    }

    last = tra.last();
    for(double i = 1; i < 50; i++)
    {
        tra << QPoint(last.x()+i, last.y());
        traret.prepend(tra.last());
    }


    last = tra.last();
    Station* s2 = new Station(Station::NonTerminus);
        s2->setCoordonnee(last + QPoint(0,5));
        s2->setNom("haut droite");
        m_stationList << s2;

    FeuStation* feuS2 = new FeuStation;
    feuS2->setCoordonnee(last+QPoint(0,-5));
    m_obstacleList << feuS2;
    feuS2->setLieu(last);
    feuS2->setNom("FeuS2");
    feuS2->addStation(s2);
    s2->addFeuStation(feuS2);
    feuS2->start();

    Trajet* traj = new Trajet;
    traj->setTrajet(tra);
    traj->setObstacle(m_obstacleList);
    m_trajetList << traj;
    Trajet* trajret = new Trajet;
    trajret->setTrajet(traret);
    trajret->setObstacle(m_obstacleList);
    m_trajetList << trajret;
    traj->setRetour(trajret);
    trajret->setRetour(traj);
//----------------------------------------------------------------------------------------------------------------------------------
    tra.clear();
    traret.clear();

    last = QPoint(25,217);

    Station* s3 = new Station(Station::NonTerminus);
        s3->setCoordonnee(last + QPoint(0,5));
        s3->setNom("bas gauche");
        m_stationList << s3;

    FeuStation* feuS3 = new FeuStation;
        feuS3->setCoordonnee(last+QPoint(0,-5));
        m_obstacleList << feuS3;
        feuS3->setLieu(last);
        feuS3->setNom("FeuS3");
        feuS3->addStation(s2);
        s3->addFeuStation(feuS3);
        feuS3->start();

    for(double i = 0; i < 50; i++)
    {
        tra << QPoint(last.x()+i, last.y());
        traret.prepend(tra.last());
    }

    last = tra.last();
    for(double i = 0; i < 1.5; i += radius)
    {
        tra << QPoint(last.x()+1+25*sin(i), last.y()-25+25*cos(i));
        traret.prepend(tra.last());
    }

    last = tra.last();
    for(double i = 1; i < 50; i++)
    {
        tra << QPoint(last.x(), last.y()-i);
        traret.prepend(tra.last());
    }

    last = tra.last();
    for(double i = 4.5; i > 3; i -= radius)
    {
        tra << QPoint(last.x()+25+25*sin(i), last.y()+3+25*cos(i));
        traret.prepend(tra.last());
    }

    last = tra.last();
    for(double i = 1; i < 75; i++)
    {
        tra << QPoint(last.x()+i, last.y());
        traret.prepend(tra.last());
    }

    last = tra.last();
    for(double i = 3; i > 1.5; i -= radius)
    {
        tra << QPoint(last.x()+25*sin(i), last.y()+25+25*cos(i));
        traret.prepend(tra.last());
    }

    last = tra.last();
    for(double i = 1; i < 50; i++)
    {
        tra << QPoint(last.x(), last.y()+i);
        traret.prepend(tra.last());
    }

    last = tra.last();
    for(double i = -1.5; i < 0; i += radius)
    {
            tra << QPoint(last.x()+25+25*sin(i), last.y()+25*cos(i));
        traret.prepend(tra.last());
    }

    last = tra.last();
    for(double i = 1; i < 50; i++)
    {
        tra << QPoint(last.x()+i, last.y());
        traret.prepend(tra.last());
    }


    last = tra.last();
    Station* s4 = new Station(Station::NonTerminus);
        s4->setCoordonnee(last + QPoint(0,5));
        s4->setNom("bas droite");
        m_stationList << s4;

    FeuStation* feuS4 = new FeuStation;
        feuS4->setCoordonnee(last+QPoint(0,-5));
        m_obstacleList << feuS4;
        feuS4->setLieu(last);
        feuS4->setNom("FeuS4");
        feuS4->addStation(s2);
        s4->addFeuStation(feuS4);
        feuS4->start();

    Trajet* traj2 = new Trajet;
    traj2->setTrajet(tra);
    traj2->setObstacle(m_obstacleList);
    m_trajetList << traj2;

    Trajet* trajret2 = new Trajet;
    trajret2->setTrajet(traret);
    m_trajetList << trajret2;

    traj2->setRetour(trajret2);
    trajret2->setRetour(traj2);


    foreach(Trajet* t , m_trajetList)
        m_trajetList << t;

}

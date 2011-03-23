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

    setupTrajet2();
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
//        feuS1->setEtat(Feu::ARRET);
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
    f1->setEtat(Feu::PASSAGE);
    f1->setSyncLight(feuS1);
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
    FeuStation * f2 = new FeuStation;
    f2->setCoordonnee(last+QPoint(0,-5));
    m_obstacleList << f2;
    f2->setLieu(last);
    f2->setNom("F2");
    f2->setEtat(Feu::ARRET);
    f2->setSyncLight(f1);
    f2->start();

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
    feuS2->setEtat(Feu::ARRET);
    feuS2->setSyncLight(f2);
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

    Tram * tram = new Tram;
    m_tramList << tram;
    tram->setTrajet(m_trajetList[0]);
    tram->start();
    Tram * tram2 = new Tram;
    m_tramList << tram2;
    tram2->setTrajet(m_trajetList[2 ]);
    tram2->start();
}
void TramWindow::setupTrajet2()
{
    QList<QPoint> tra, traret;
    QPoint last(25,250);

    m_stationList << new Station(Station::NonTerminus);
    m_stationList.last()->setCoordonnee(last + QPoint(0,-7));
    m_stationList.last()->setNom("bas droite");

    FeuStation* feustation = new FeuStation;
    FeuStation* feustation2 = new FeuStation;

    feustation->setCoordonnee(last+QPoint(5,5));
    feustation->setLieu(last);
    feustation->setNom("FeuS4");
    feustation->addStation(m_stationList.last());
    m_stationList.last()->addFeuStation(feustation);
    m_obstacleList << feustation;
    feustation->start();


    for(double i = 0; i < 250; i++)
    {
        tra << QPoint(last.x()+i, last.y());
        traret.prepend(tra.last()+QPoint(0,32));
    }
    last = tra.last();
    QPoint lastret = traret.last();

    Feu * feu = new Feu;
    feu->setCoordonnee(last+QPoint(-200,5));
    m_obstacleList << feu;
    feu->setLieu(last+QPoint(-200,0));
    feu->setNom("F1");
    feu->setEtat(Feu::PASSAGE);
    feu->setSyncLight(feustation);
    feu->start();

    Feu * feuret = new Feu;
    feuret->setCoordonnee(lastret+QPoint(200,5));
    m_obstacleList << feuret;
    feuret->setLieu(lastret+QPoint(200,0));
    feuret->setNom("F1");
    feuret->setEtat(Feu::PASSAGE);
    feuret->setSyncLight(feustation2);
    feuret->start();

    Feu * feu1 = new Feu;
    feu1->setCoordonnee(last+QPoint(-150,5));
    m_obstacleList << feu1;
    feu1->setLieu(last+QPoint(-150,0));
    feu1->setNom("F2");
    feu1->setEtat(Feu::PASSAGE);
    feu1->setSyncLight(feu);
    feu1->start();

    Feu * feuret1 = new Feu;
    feuret1->setCoordonnee(lastret+QPoint(150,5));
    m_obstacleList << feuret1;
    feuret1->setLieu(lastret+QPoint(150,0));
    feuret1->setNom("F1");
    feuret1->setEtat(Feu::PASSAGE);
    feuret1->setSyncLight(feuret);
    feuret1->start();

    Feu * feu2 = new Feu;
    feu2->setCoordonnee(last+QPoint(-100,5));
    m_obstacleList << feu2;
    feu2->setLieu(last+QPoint(-100,0));
    feu2->setNom("F3");
    feu2->setEtat(Feu::PASSAGE);
    feu2->setSyncLight(feu1);
    feu2->start();

    Feu * feuret2 = new Feu;
    feuret2->setCoordonnee(lastret+QPoint(100,5));
    m_obstacleList << feuret2;
    feuret2->setLieu(lastret+QPoint(100,0));
    feuret2->setNom("F1");
    feuret2->setEtat(Feu::PASSAGE);
    feuret2->setSyncLight(feuret1);
    feuret2->start();


    Feu * feu3 = new Feu;
    feu3->setCoordonnee(last+QPoint(-50,5));
    m_obstacleList << feu3;
    feu3->setLieu(last+QPoint(-50,0));
    feu3->setNom("F3");
    feu3->setEtat(Feu::PASSAGE);
    feu3->setSyncLight(feu2);
    feu3->start();

    Feu * feuret3 = new Feu;
    feuret3->setCoordonnee(lastret+QPoint(50,5));
    m_obstacleList << feuret3;
    feuret3->setLieu(lastret+QPoint(50,0));
    feuret3->setNom("F1");
    feuret3->setEtat(Feu::PASSAGE);
    feuret3->setSyncLight(feuret2);
    feuret3->start();
    feustation->setSyncLight(feuret3);

    m_stationList << new Station(Station::NonTerminus);
    m_stationList.last()->setCoordonnee(last + QPoint(0,-7));
    m_stationList.last()->setNom("bas droite");

    feustation2->setCoordonnee(last+QPoint(-5,5));
    feustation2->setLieu(last);
    feustation2->setNom("FeuS3");
    feustation2->setSyncLight(feu3);
    feustation2->addStation(m_stationList.last());
    m_stationList.last()->addFeuStation(feustation2);
    m_obstacleList << feustation2;
    feustation2->start();

    for(double i = 1; i < 30; i++)
    {
        tra << QPoint(last.x(), last.y()+i);
        traret.append(last+QPoint(-250,31-i));
    }

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

    Tram * tram = new Tram;
    m_tramList << tram;
    tram->setTrajet(m_trajetList.first());
    tram->start();

    Tram * tram2 = new Tram;
    m_tramList << tram2;
    tram2->setTrajet(m_trajetList.last());
    tram2->start();
    Tram * tram3 = new Tram;
    m_tramList << tram3;
    tram3->setTrajet(m_trajetList.first());
    tram3->setCoordonnee(QPoint(80,250));
    tram3->start();
//    Tram * tram4 = new Tram;
//    m_tramList << tram4;
//    tram4->setTrajet(m_trajetList[1]);
//    tram4->start();
//    Tram * tram5 = new Tram;
//    m_tramList << tram5;
//    tram5->setTrajet(m_trajetList[1]);
//    tram5->start();
//    Tram * tram6 = new Tram;
//    m_tramList << tram6;
//    tram6->setTrajet(m_trajetList[1]);
//    tram6->start();
}

/*
 *   Copyright 2011 by Alexandre Mendes <alex.mendes1988@gmail.com>
 *   Copyright 2011 by Bertrand Pages <pages.bertrand@gmail.com>
 *   Copyright 2011 by Guillaume Hormiere <hormiere.guillaume@gmail.com>
 *   Copyright 2011 by Nicolas Noullet <nicolas.noullet@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "TramWindow.h"
#include "ui_tramwindow.h"
#include "TramPropertiesWidget.h"
#include "Tram.h"
#include "Station.h"
#include "Light.h"
#include "StationLight.h"
#include "Trip.h"
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

    setupTrip2();
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

void TramWindow::setupTrip1()
{
    QList<QPoint> tra, traret;
    QPoint last(25,25);
    double radius = 0.05;
    Station* s1 = new Station(Station::NonTerminus);
        s1->setCoordinate(last + QPoint(0,5));
        s1->setName("haut gauche");
        m_stationList << s1;

        StationLight* feuS1 = new StationLight;
        feuS1->setCoordinate(last+QPoint(0,-5));
        m_obstacleList << feuS1;
        feuS1->setPlace(last);
        feuS1->setName("LightS1");
//        feuS1->setColor(Light::Red);
        feuS1->addStation(s1);
        s1->addStationLight(feuS1);
        feuS1->start();





    for(double i = 0; i < 50; i++)
    {
        tra << QPoint(last.x()+i, last.y());
        traret.prepend(tra.last());
    }

    last = tra.last();
    Light * f1 = new Light;
    f1->setCoordinate(last+QPoint(0,-5));
    m_obstacleList << f1;
    f1->setPlace(last);
    f1->setName("F1");
    f1->setColor(Light::Green);
    f1->setPreviousLight(feuS1);
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
    StationLight * f2 = new StationLight;
    f2->setCoordinate(last+QPoint(0,-5));
    m_obstacleList << f2;
    f2->setPlace(last);
    f2->setName("F2");
    f2->setColor(Light::Red);
    f2->setPreviousLight(f1);
    f2->start();

    last = tra.last();
    for(double i = 1; i < 50; i++)
    {
        tra << QPoint(last.x()+i, last.y());
        traret.prepend(tra.last());
    }


    last = tra.last();
    Station* s2 = new Station(Station::NonTerminus);
        s2->setCoordinate(last + QPoint(0,5));
        s2->setName("haut droite");
        m_stationList << s2;

    StationLight* feuS2 = new StationLight;
    feuS2->setCoordinate(last+QPoint(0,-5));
    m_obstacleList << feuS2;
    feuS2->setPlace(last);
    feuS2->setName("LightS2");
    feuS2->setColor(Light::Red);
    feuS2->setPreviousLight(f2);
    feuS2->addStation(s2);
    s2->addStationLight(feuS2);
    feuS2->start();

    Trip* traj = new Trip;
    traj->setTrip(tra);
    traj->setObstacle(m_obstacleList);
    m_trajetList << traj;
    Trip* trajret = new Trip;
    trajret->setTrip(traret);
    trajret->setObstacle(m_obstacleList);
    m_trajetList << trajret;
    traj->setForward(trajret);
    trajret->setForward(traj);
//----------------------------------------------------------------------------------------------------------------------------------
    tra.clear();
    traret.clear();

    last = QPoint(25,217);

    Station* s3 = new Station(Station::NonTerminus);
        s3->setCoordinate(last + QPoint(0,5));
        s3->setName("bas gauche");
        m_stationList << s3;

    StationLight* feuS3 = new StationLight;
        feuS3->setCoordinate(last+QPoint(0,-5));
        m_obstacleList << feuS3;
        feuS3->setPlace(last);
        feuS3->setName("LightS3");
        feuS3->addStation(s2);
        s3->addStationLight(feuS3);
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
        s4->setCoordinate(last + QPoint(0,5));
        s4->setName("bas droite");
        m_stationList << s4;

    StationLight* feuS4 = new StationLight;
        feuS4->setCoordinate(last+QPoint(0,-5));
        m_obstacleList << feuS4;
        feuS4->setPlace(last);
        feuS4->setName("LightS4");
        feuS4->addStation(s2);
        s4->addStationLight(feuS4);
        feuS4->start();

    Trip* traj2 = new Trip;
    traj2->setTrip(tra);
    traj2->setObstacle(m_obstacleList);
    m_trajetList << traj2;

    Trip* trajret2 = new Trip;
    trajret2->setTrip(traret);
    m_trajetList << trajret2;

    traj2->setForward(trajret2);
    trajret2->setForward(traj2);


    foreach(Trip* t , m_trajetList)
        m_trajetList << t;

    Tram * tram = new Tram;
    m_tramList << tram;
    tram->setTrip(m_trajetList[0]);
    tram->start();
    Tram * tram2 = new Tram;
    m_tramList << tram2;
    tram2->setTrip(m_trajetList[2 ]);
    tram2->start();
}
void TramWindow::setupTrip2()
{
    QList<QPoint> tra, traret;
    QPoint last(25,250);

    m_stationList << new Station(Station::NonTerminus);
    m_stationList.last()->setCoordinate(last + QPoint(0,-7));
    m_stationList.last()->setName("bas droite");

    StationLight* feustation = new StationLight;
    StationLight* feustation2 = new StationLight;

    feustation->setCoordinate(last+QPoint(5,5));
    feustation->setPlace(last+QPoint(1,0));
    feustation->setName("LightS4");
    feustation->addStation(m_stationList.last());
    m_stationList.last()->addStationLight(feustation);
    m_obstacleList << feustation;
    feustation->start();

    for(double i = 0; i < 250; i++)
    {
        tra << QPoint(last.x()+i, last.y());
        traret.prepend(tra.last()+QPoint(0,32));
    }
    last = tra.last();
    QPoint lastret = traret.last();

    Light * feu = new Light;
    feu->setCoordinate(last+QPoint(-200,5));
    m_obstacleList << feu;
    feu->setPlace(last+QPoint(-200,0));
    feu->setName("F1");
    feu->setColor(Light::Green);
    feu->setPreviousLight(feustation);
    feu->start();

    Light * feuret = new Light;
    feuret->setCoordinate(lastret+QPoint(200,5));
    m_obstacleList << feuret;
    feuret->setPlace(lastret+QPoint(200,0));
    feuret->setName("F1");
    feuret->setColor(Light::Green);
    feuret->setPreviousLight(feustation2);
    feuret->start();

    Light * feu1 = new Light;
    feu1->setCoordinate(last+QPoint(-150,5));
    m_obstacleList << feu1;
    feu1->setPlace(last+QPoint(-150,0));
    feu1->setName("F2");
    feu1->setColor(Light::Green);
    feu1->setPreviousLight(feu);
    feu1->start();

    Light * feuret1 = new Light;
    feuret1->setCoordinate(lastret+QPoint(150,5));
    m_obstacleList << feuret1;
    feuret1->setPlace(lastret+QPoint(150,0));
    feuret1->setName("F1");
    feuret1->setColor(Light::Green);
    feuret1->setPreviousLight(feuret);
    feuret1->start();

    Light * feu2 = new Light;
    feu2->setCoordinate(last+QPoint(-100,5));
    m_obstacleList << feu2;
    feu2->setPlace(last+QPoint(-100,0));
    feu2->setName("F3");
    feu2->setColor(Light::Green);
    feu2->setPreviousLight(feu1);
    feu2->start();

    Light * feuret2 = new Light;
    feuret2->setCoordinate(lastret+QPoint(100,5));
    m_obstacleList << feuret2;
    feuret2->setPlace(lastret+QPoint(100,0));
    feuret2->setName("F1");
    feuret2->setColor(Light::Green);
    feuret2->setPreviousLight(feuret1);
    feuret2->start();


    Light * feu3 = new Light;
    feu3->setCoordinate(last+QPoint(-50,5));
    m_obstacleList << feu3;
    feu3->setPlace(last+QPoint(-50,0));
    feu3->setName("F3");
    feu3->setColor(Light::Green);
    feu3->setPreviousLight(feu2);
    feu3->start();

    Light * feuret3 = new Light;
    feuret3->setCoordinate(lastret+QPoint(50,5));
    m_obstacleList << feuret3;
    feuret3->setPlace(lastret+QPoint(50,0));
    feuret3->setName("F1");
    feuret3->setColor(Light::Green);
    feuret3->setPreviousLight(feuret2);
    feuret3->start();
    feustation->setPreviousLight(feuret3);

    m_stationList << new Station(Station::NonTerminus);
    m_stationList.last()->setCoordinate(last + QPoint(0,-7));
    m_stationList.last()->setName("bas droite");

    feustation2->setCoordinate(last+QPoint(-5,5));
    feustation2->setPlace(last);
    feustation2->setName("LightS3");
    feustation2->setPreviousLight(feu3);
    feustation2->addStation(m_stationList.last());
    m_stationList.last()->addStationLight(feustation2);
    m_obstacleList << feustation2;
    feustation2->start();

    for(double i = 1; i < 30; i++)
    {
        tra << QPoint(last.x(), last.y()+i);
        traret.append(last+QPoint(-250,31-i));
    }

    Trip* traj = new Trip;
    traj->setTrip(tra);
    traj->setObstacle(m_obstacleList);
    m_trajetList << traj;
    Trip* trajret = new Trip;
    trajret->setTrip(traret);
    trajret->setObstacle(m_obstacleList);
    m_trajetList << trajret;
    traj->setForward(trajret);
    trajret->setForward(traj);

    Tram * tram = new Tram;
    m_tramList << tram;
    tram->setTrip(m_trajetList.first());
    tram->setName("Tram1");
    tram->start();

    Tram * tram2 = new Tram;
    m_tramList << tram2;
    tram2->setTrip(m_trajetList.last());
    tram2->setName("Tram2");
    tram2->start();

    Tram * tram3 = new Tram;
    m_tramList << tram3;
    tram3->setTrip(m_trajetList.first());
    tram3->setCoordinate(QPoint(80,250));
    tram3->setName("Tram3");
    tram3->start();

    Tram * tram4 = new Tram;
    m_tramList << tram4;
    tram4->setTrip(m_trajetList.last());
    tram4->setCoordinate(QPoint(80,282));
    tram4->setName("Tram4");
    tram4->start();

    Tram * tram5 = new Tram;
    m_tramList << tram5;
    tram5->setTrip(m_trajetList.last());
    tram5->setCoordinate(QPoint(151,282));
    tram5->setName("Tram5");
    tram5->start();

//    Tram * tram5 = new Tram;
//    m_tramList << tram5;
//    tram5->setTrip(m_trajetList[1]);
//    tram5->start();
//    Tram * tram6 = new Tram;
//    m_tramList << tram6;
//    tram6->setTrip(m_trajetList[1]);
//    tram6->start();
}

#ifndef TRAMWINDOW_H
#define TRAMWINDOW_H

#include <QMainWindow>
#include "Trajet.h"
#include "Obstacle.h"
#include "Tram.h"
#include "Station.h"
#include "Timer.h"
#include "ObstacleWidget.h"
#include "TramPropertiesWidget.h"

namespace Ui {
    class TramWindow;
}

class TramWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TramWindow(QWidget *parent = 0);
    virtual ~TramWindow();
    void setupTrajet();
    void setupTrajet2();
    void setupDrawingWidget();

private:
    QList<Trajet*> m_trajetList;
    QList<Tram*> m_tramList;
    QList<Obstacle*> m_obstacleList;
    QList<ObstacleWidget*> m_obstacleWidgetList;
    QList<TramPropertiesWidget*> m_tramPropertiesWidgetList;
    QList<Station*> m_stationList;

    Ui::TramWindow *ui;
    Timer *m_timer;
};

#endif // TRAMWINDOW_H

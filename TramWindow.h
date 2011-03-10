#ifndef TRAMWINDOW_H
#define TRAMWINDOW_H

#include <QMainWindow>
#include "Trajet.h"
#include "Obstacle.h"
#include "Tram.h"
#include "Station.h"

namespace Ui {
    class TramWindow;
}

class TramWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TramWindow(QWidget *parent = 0);
    ~TramWindow();
    void setupTrajet();
    void setupDrawingWidget();

private:
    QList<Trajet*> m_trajetList;
    QList<Tram*> m_tramList;
    QList<Obstacle*> m_obstacleList;
//    QList<Station*> m_stationList;

    Ui::TramWindow *ui;
};

#endif // TRAMWINDOW_H

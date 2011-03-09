#ifndef OBSTACLEWIDGET_H
#define OBSTACLEWIDGET_H

#include <QWidget>
#include "Obstacle.h"

namespace Ui {
    class ObstacleWidget;
}

class ObstacleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ObstacleWidget(Obstacle* obstacle, QWidget *parent = 0);
    ~ObstacleWidget();

private slots:
    void updateObstacleInformation();
private:
    Ui::ObstacleWidget *ui;
    QTimer *m_timer;
    Obstacle *m_obstacle;
};

#endif // OBSTACLEWIDGET_H

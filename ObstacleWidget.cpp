#include "ObstacleWidget.h"
#include "ui_obstaclewidget.h"
#include <QTimer>

ObstacleWidget::ObstacleWidget(Obstacle *obstacle, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObstacleWidget)
{
    m_obstacle = obstacle;
    ui->setupUi(this);
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateObstacleInformation()));
    m_timer->start(50);
}

ObstacleWidget::~ObstacleWidget()
{
    delete ui;
}

void ObstacleWidget::updateObstacleInformation()
{
    this->ui->m_nom->setText(m_obstacle->nom());
    if(m_obstacle->indiquerPassage())
    {
        this->ui->m_etat->setCheckState(Qt::Unchecked);
    }
    else
    {
        this->ui->m_etat->setCheckState(Qt::Checked);
    }
}

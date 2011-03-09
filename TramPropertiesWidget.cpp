#include "TramPropertiesWidget.h"
#include "ui_trampropertieswidget.h"
#include "Tram.h"
TramPropertiesWidget::TramPropertiesWidget(Tram* t, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TramPropertiesWidget)
{
    ui->setupUi(this);
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTramInformation()));
    m_timer->start(50);
    m_tram = t;
}

TramPropertiesWidget::~TramPropertiesWidget()
{
    delete ui;
}

void TramPropertiesWidget::updateTramInformation()
{
    this->ui->m_vitesse->setText(QString::number(m_tram->vitesse()));
    switch(m_tram->etat())
    {
    case Tram::MARCHE:
        this->ui->m_etat->setText("Marche");
        break;
    case Tram::ARRET:
        this->ui->m_etat->setText("Arret");
        break;
    }
}

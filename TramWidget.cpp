#include "TramWidget.h"
#include <QtGui/QPaintEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QPainter>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include <QDebug>

TramWidget::TramWidget(QWidget *parent)
   :QWidget(parent), m_pixmap(1000,600)
{

    setFocusPolicy(Qt::StrongFocus);
    qsrand(QTime::currentTime().second());

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));

    m_timer->start(50);

}

TramWidget::~TramWidget() {
}
void TramWidget::paintEvent(QPaintEvent *event)
{
        QPainter painter(this);
        m_pixmap.fill(Qt::white);
        painter.drawPixmap(0,0,m_pixmap);

        for(int i = 0; i < m_drawableList.size(); i++)
        {
            m_drawableList[i]->draw(&painter);
        }
}


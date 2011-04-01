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

#include "TramWidget.h"
#include <QtGui/QPaintEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QPainter>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include <QDebug>

TramWidget::TramWidget(QWidget *parent)
    : QWidget(parent), m_pixmap(1000, 600)
{

    setFocusPolicy(Qt::StrongFocus);
    qsrand(QTime::currentTime().second());

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));

    m_timer->start(50);

}

TramWidget::~TramWidget()
{
}
void TramWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    m_pixmap.fill(Qt::black);
    painter.drawPixmap(0, 0, m_pixmap);

    for(int i = 0; i < m_drawableList.size(); i++) {
        m_drawableList[i]->draw(&painter);
    }
}


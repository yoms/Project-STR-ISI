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

#include <QtGui/QWidget>
#include <QList>
#include "Drawable.h"
#include "Trip.h"

#ifndef TRAMWIDGET_H_
#define TRAMWIDGET_H_

/**
 * @brief Représente un widget qui affiche le nom et l'état d'un tramway de l'application.
 */
class TramWidget : public QWidget  {
        Q_OBJECT

public:
        /**
         * @brief Construit le widget.
         * @param l'objet parent
         */
        explicit TramWidget(QWidget *parent = 0);
        /**
         * @brief Détruit le widget.
         */
        virtual ~TramWidget();
        /**
         * @brief Change la liste d'objets graphiques.
         * @param la nouvelle liste
         */
        void setDrawableList(QList<Drawable* > &d){m_drawableList = d;}

protected:
        void paintEvent(QPaintEvent *event);
private:
        void setupTrip();

        QTimer *m_timer;
        QPixmap m_pixmap;
        QList<Drawable* > m_drawableList;
};

#endif /* TRAMWIDGET_H_ */

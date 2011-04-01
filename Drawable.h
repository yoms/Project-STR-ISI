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
#ifndef DRAWABLE_H
#define DRAWABLE_H
#include <QPoint>
#include <QString>
class QPainter;

/**
 * @brief Représente un objet graphique.
 */
class Drawable
{
public:
    /**
     * @brief Construit un objet graphique.
     */
    Drawable();
    /**
     * @brief Dessine un objet graphique.
     * @param
     */
    virtual void draw(QPainter*) = 0;
    /**
     * @brief Dessine un élément
     * @param
     * @param l'abscisse
     * @param l'ordonnée
     * @param la taille
     */
    void drawElemScen(QPainter*, int, int, int);
    /**
     * @brief Indique la position de l'objet.
     * @return la position de l'objet
     */
    QPoint coordinate() {
        return m_coordinate;
    }
    /**
     * @brief Change la position de l'objet.
     * @param la nouvelle position de l'objet
     */
    void setCoordinate(QPoint p) {
        m_coordinate = p;
    }
    /**
     * @brief Indique le nom de l'objet graphique.
     * @return le nom
     */
    QString name() {
        return m_name;
    }
    /**
     * @brief Change le nom de l'objet graphique.
     * @param le nouveau nom
     */
    void setName(QString n) {
        m_name = n;
    }
    /**
     * @brief Met en surbrillance l'objet.
     */
    void select() {
        m_selected = true;
    }
    /**
     * @brief Enleve la surbrillance de l'objet.
     */
    void unSelect() {
        m_selected = false;
    }
    /**
     * @brief Retourne vrai si l'objet est en surbrillance ou pas.
     * @return Vrai si l'objet est en surbrillance, faut sinon.
     */
    bool isSelect() {
        return m_selected;
    }

protected:
    QPoint m_coordinate;
private:
    QString m_name;
    bool m_selected;
};

#endif // DRAWABLE_H

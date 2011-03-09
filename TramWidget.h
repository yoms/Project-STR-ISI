#include <QtGui/QWidget>
#include <QList>
#include "Drawable.h"
#include "Stepable.h"
#include "Trajet.h"

#ifndef TRAMWIDGET_H_
#define TRAMWIDGET_H_

class TramWidget : public QWidget  {
        Q_OBJECT

public:
        explicit TramWidget(QWidget *parent = 0);
        virtual ~TramWidget();
        void setDrawableList(QList<Drawable* > &d){m_drawableList = d;}

protected:
        void paintEvent(QPaintEvent *event);
private:
        void setupTrajet();

        QTimer *m_timer;
        QPixmap m_pixmap;
        QList<Drawable* > m_drawableList;
};

#endif /* TRAMWIDGET_H_ */

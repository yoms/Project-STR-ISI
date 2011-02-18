#include <QtGui/QWidget>
#include "Drawable.h"
#include "Trajet.h"

#ifndef TRAMWIDGET_H_
#define TRAMWIDGET_H_

class TramWidget : public QWidget  {
        Q_OBJECT

public:
        explicit TramWidget(QWidget *parent = 0);
        virtual ~TramWidget();

protected:
        void paintEvent(QPaintEvent *event);

private:
        void setupTrajet();

        QTimer *m_timer;
        QList<Trajet*> m_trajetList;
        QPixmap m_pixmap;
        QList<Drawable*> m_itemList;
};

#endif /* TRAMWIDGET_H_ */

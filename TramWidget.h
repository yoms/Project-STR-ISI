#include <QtGui/QWidget>
#include "Drawable.h"
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
        QTimer *timer;
        QTimer *createTimer;
        QPixmap pixmap;
        QList<Drawable*> itemList;
};

#endif /* TRAMWIDGET_H_ */

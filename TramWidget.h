#include <QtGui/QWidget>

#ifndef TRAMWIDGET_H_
#define TRAMWIDGET_H_

class TramWidget : public QWidget  {
        Q_OBJECT

public:
        explicit TramWidget(QWidget *parent = 0);
        virtual ~TramWidget();

protected:
        void paintEvent(QPaintEvent *event);
        void keyPressEvent (QKeyEvent *event);

private:
        QTimer *timer;
        QTimer *createTimer;
        QPixmap pixmap;
        QPolygon soliter;
        QPolygon foot;
        QPolygon rectScen;
        QPolygon currentLevel;
        QPoint shiftPoint;

        int len;
        int startlen;
        enum Napr {Up, Down, Left, Right};
        Napr napr;
        Napr tempState;
        bool pause;
        int level;
        int live;
        int finishLen;

        void createLevel();
        void drawScen();
        void nextLevel();
        void coordSoliter();
        void drawElemScen(QPainter *painter, int X, int Y);
        void drawSoliter(QPainter *painter);
        void drawFoot(QPainter *painter);

private slots:
        void rebuild();
        void createFoot();
        void pauseUpdate();
        void dead();

public slots:
        void newGame();

signals:
        void lenSoliter(int num);
        void setLive(int num);
        void setLevel(int num);
        void setTarget(int num);
};

#endif /* TRAMWIDGET_H_ */

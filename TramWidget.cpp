#include "TramWidget.h"

#include <QtGui/QPaintEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QPainter>
#include <QtCore/QTimer>
#include <QtCore/QTime>

TramWidget::TramWidget(QWidget *parent)
   :QWidget(parent), pixmap(1000,600), shiftPoint(0,0), len(15), startlen(3),
    pause(false),level(1), live(3), finishLen(150) {

        setFocusPolicy(Qt::StrongFocus);
        qsrand(QTime::currentTime().second());

        napr = Right;
        tempState = Right;

        timer = new QTimer(this);
        timer->setInterval(50);
        connect(timer, SIGNAL(timeout()), this, SLOT(rebuild()));

        createTimer = new QTimer(this);
        createTimer->setInterval(40);
        connect(createTimer, SIGNAL(timeout()), SLOT(createFoot()));

        coordSoliter();
        createLevel();
        drawScen();
}

TramWidget::~TramWidget() {
}

void TramWidget::createLevel()
{
        for(int i=0; i!=44; i++)
                rectScen << QPoint(0, i);
        for(int i=0; i!=65; i++)
                rectScen << QPoint(i, 44);
        for(int i=0; i!=44; i++)
                rectScen << QPoint(64, i);
        for(int i=0; i!=64; i++)
                rectScen << QPoint(i, 0);
        currentLevel.clear();

}

void TramWidget::paintEvent(QPaintEvent *event)
{
        QPainter painter(this);
        painter.drawPixmap(0,0,pixmap);
        drawFoot(&painter);
        drawSoliter(&painter);

        if(!live) {
                painter.setPen(Qt::white);
                painter.setFont(QFont("Segoe Print", 38));
                painter.drawText(rect() ,Qt::AlignCenter, tr(" "));
        }

}

void TramWidget::keyPressEvent(QKeyEvent *event)
{
        switch(event->key()) {
        case Qt::Key_Up:
                if (napr != Down) {
                        if(!timer->isActive() && live && !pause) timer->start();
                        tempState = Up;
                        shiftPoint = QPoint(0,-1);
                }
                break;
        case Qt::Key_Down:
                if (napr != Up) {
                        if(!timer->isActive() && live && !pause) timer->start();
                        tempState = Down;
                        shiftPoint = QPoint(0,1);
                }
                break;
        case Qt::Key_Left:
                if (napr != Right) {
                        if(!timer->isActive() && live && !pause) timer->start();
                        tempState = Left;
                        shiftPoint = QPoint(-1,0);
                }
                break;
        case Qt::Key_Right:
                if (napr != Left) {
                        if(!timer->isActive() && live && !pause) timer->start();
                        tempState = Right;
                        shiftPoint = QPoint(1,0);
                }
                break;
        case Qt::Key_Space:
                if(pause && live) {
                        pause = false;
                        timer->start();
                } else {
                        pause = true;
                        timer->stop();
                        createTimer->stop();
                }
                break;
        default:
                QWidget::keyPressEvent(event);
        }
}

void TramWidget::drawScen()
{
        QPainter painter(&pixmap);
        painter.setPen(Qt::darkGray);
        painter.setBrush(QBrush(Qt::darkGray));

        createLevel();
        pixmap.fill(Qt::black);

        for(int i=0; i!=rectScen.size(); i++)
                drawElemScen(&painter, rectScen.point(i).x(), rectScen.point(i).y());

        for(int i=0; i!=currentLevel.size(); i++)
                drawElemScen(&painter, currentLevel.point(i).x(), currentLevel.point(i).y());

        switch(level) {
        case 1:
                finishLen = 15;
                break;
        case 2:
                finishLen = 26;
                break;
        case 3:
                finishLen = 30;
                break;
        case 4:
                finishLen = 35;
                break;
        case 5:
                finishLen = 40;
                break;
        default:
                finishLen =9999999;
        }
        emit setTarget(finishLen);
}

void TramWidget::drawElemScen(QPainter *painter, int X, int Y)
{
        QRectF rect(6,6,10,10);
        rect.moveCenter(rect.center() + QPointF(12*X, 12*Y));
        painter->drawRect(rect);
}

void TramWidget::drawSoliter(QPainter *painter)
{
        painter->save();
        painter->setPen(Qt::red);
        painter->setBrush(QBrush(Qt::red));

        drawElemScen(painter, soliter.first().x(), soliter.first().y());
        painter->setPen(Qt::darkGray);
        painter->setBrush(QBrush(Qt::darkGray));

        for(int i=1; i!=soliter.size(); i++) {
                drawElemScen(painter, soliter.point(i).x(), soliter.point(i).y());
        }

        painter->restore();
}

void TramWidget::drawFoot(QPainter *painter)
{
        painter->save();
        painter->setPen(Qt::red);
        painter->setBrush(QBrush(Qt::red));

        for(int i=0; i!=foot.size(); i++) {
                drawElemScen(painter, foot.point(i).x(), foot.point(i).y());
        }

        painter->restore();
}

void TramWidget::rebuild()
{
        napr = tempState;
        if(!createTimer->isActive()) createTimer->start();

        for(int i=soliter.size()-1; i!=0; i--) {
                soliter.setPoint(i,soliter.point(i-1));
        }

        QPoint point = soliter.first() + shiftPoint;
        if(foot.contains(point)) {
                soliter.prepend(point);
                foot.remove(foot.indexOf(point));
                emit lenSoliter(soliter.size());
                if(soliter.size() == finishLen) nextLevel();
        } else if(soliter.contains(point) || currentLevel.contains(point)) {
                dead();
        } else if (point.x()== 0 || point.x() == 64 || point.y() == 0 || point.y() == 44) {
                dead();
        } else {
                soliter.first() = point;
        }

        update();
}

void TramWidget::createFoot()
{
        if(foot.size() < 3) {
                forever {
                        QPoint point((qrand()%63)+1, (qrand()%43)+1);
                        if (!soliter.contains(point) && !currentLevel.contains(point)) {
                                foot << point;
                                break;
                        }
                }
        }
}

void TramWidget::newGame()
{
        napr = Right;
        pause = false;
        timer->stop();
        createTimer->stop();
        soliter.clear();
        foot.clear();
        level = 1;
        live = 3;
        coordSoliter();
        emit setLive(live);
        emit setLevel(level);
        emit lenSoliter(3);
        drawScen();
        update();
}

void TramWidget::dead()
{
        napr = Right;
        pause = true;
        timer->stop();
        createTimer->stop();
        live -= 1;
        emit setLive(live);
        emit lenSoliter(3);
        QTimer::singleShot(1500, this, SLOT(pauseUpdate()));
}

void TramWidget::pauseUpdate()
{
        if(live) {
                pause = false;
                soliter.clear();
                foot.clear();
                coordSoliter();
        }
        update();
}

void TramWidget::nextLevel()
{
        level++;
        live++;
        emit setLevel(level);
        emit setLive(live);
        emit lenSoliter(3);

        napr = Right;
        timer->stop();
        createTimer->stop();

        drawScen();
        coordSoliter();

        foot.clear();
        update();

}


void TramWidget::coordSoliter()
{
        soliter.clear();
        switch(level) {
                case 1:
                        soliter << QPoint(33,22) << QPoint(32,22) << QPoint(31,22);
                        break;
                case 2:
                        soliter << QPoint(6,22) << QPoint(5,22) << QPoint(4,22);
                        break;
                case 3:
                        soliter << QPoint(6,8) << QPoint(5,8) << QPoint(4,8);
                        break;
                case 4:
                        soliter << QPoint(6,3) << QPoint(5,3) << QPoint(4,3);
                        break;
                default:
                        soliter << QPoint(6,3) << QPoint(5,3) << QPoint(4,3);
        }
}



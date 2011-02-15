#ifndef TRAMWINDOW_H
#define TRAMWINDOW_H

#include <QMainWindow>

namespace Ui {
    class TramWindow;
}

class TramWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TramWindow(QWidget *parent = 0);
    ~TramWindow();

private:
    Ui::TramWindow *ui;
};

#endif // TRAMWINDOW_H

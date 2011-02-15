#include "TramWindow.h"
#include "ui_tramwindow.h"

TramWindow::TramWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TramWindow)
{
    ui->setupUi(this);
}

TramWindow::~TramWindow()
{
    delete ui;
}

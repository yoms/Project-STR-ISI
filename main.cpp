#include "TramWindow.h"

#include <QtGui/QApplication>
#include <QtCore/QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));
    TramWindow w;
    w.show();
    return a.exec();
}

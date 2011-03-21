#include "TramWindow.h"
#include <QtGui/QApplication>
#include <QtCore/QTextCodec>

extern "C" {
extern void adainit (void);
extern void adafinal (void);
}

int main(int argc, char *argv[])
{
//    adainit();
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));
    TramWindow w;
    w.show();
//    adafinal();
    return a.exec();
}

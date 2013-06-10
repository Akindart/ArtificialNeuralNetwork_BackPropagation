#include "mainwindow.h"
#include <QApplication>

#include "ann_bp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //qDebug()<<exp(-2*0.74652);

    return a.exec();
}

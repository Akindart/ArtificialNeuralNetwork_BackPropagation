#include "mainwindow.h"
#include <QApplication>

#include "ann_bp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    ANN_BP *ann_bp = new ANN_BP(NULL, 6, 5, 5);

    QList<double> inputs;

    inputs.append(0.43);
    inputs.append(0.23);
    inputs.append(0.0);
    inputs.append(0.7234);
    inputs.append(1);
    inputs.append(0.574);
    inputs.append(1);

    ann_bp->exeANNBP(inputs, true, true);

    return a.exec();
}

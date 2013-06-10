#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QProgressDialog>
#include <QAbstractTableModel>
#include <QLabel>
#include <QFont>
#include <QHash>

#include "ann_bp.h"
#include "confusionmatrix.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAbrir_arquivo_de_treinamento_triggered();
    void on_actionAbrir_arquivo_de_teste_triggered();
    void on_actionSalvar_matriz_de_confusao_triggered();
    void on_btnCreateNet_clicked();

    void on_btnTraining_clicked();

    void on_btnRunTest_clicked();

public slots:
    void updateConfusionMatrix();

private:
    Ui::MainWindow *ui;

    QFile *traningFile;
    QFile *testFile;
    QHash<int, QList<double> > *tempList;
    QHash<int, QList<double> > *testList;
    int qtyInput;
    int qtyHidden;
    int qtyOutput;
    ANN_BP *artificialNN;
    QList< QStringList > *stringsToNormalize;

    void fileParse(QString fn);
    void fileTestParse(QString fn);
    void normalize();
    void normalizeTest();
    void updateTableNormalized();
    void updateTestTableNormalized();

    void calcLayers();
    void saveConfusionMatrix();
    void processing(bool b);

signals:
    void tableUpdated();


};

#endif // MAINWINDOW_H

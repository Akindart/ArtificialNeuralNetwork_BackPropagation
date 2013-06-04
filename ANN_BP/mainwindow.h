#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QTreeView>
#include <QSplitterHandle>
#include <QFile>
#include <QFileDialog>
#include <QDebug>


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

private:
    Ui::MainWindow *ui;

    QFile *traningFile;
    QFile *testFile;

};

#endif // MAINWINDOW_H

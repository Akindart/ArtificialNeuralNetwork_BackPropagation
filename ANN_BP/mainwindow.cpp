#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbrir_arquivo_de_treinamento_triggered()
{

    QString trainingFileName = QFileDialog::getOpenFileName(this, tr("Arquivo de treinamento"), "/home/spades", "Text files (*.txt)");


    this->traningFile = new QFile(trainingFileName);

}

void MainWindow::on_actionAbrir_arquivo_de_teste_triggered()
{

    QString testFileName = QFileDialog::getOpenFileName(this, tr("Arquivo de Teste"), "/home/spades", "Text files (*.txt)");

    this->testFile = new QFile(testFileName);

}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, SIGNAL(tableUpdated()),
            ui->tableWidget, SLOT(resizeColumnsToContents()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbrir_arquivo_de_treinamento_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,
                                                     "Abrir arquivo",
                                                     "",
                                                     "CSV (*.csv);; TXT (*.txt)");

    fileParse(file_name);
    this->traningFile = new QFile(file_name);

}

void MainWindow::on_actionAbrir_arquivo_de_teste_triggered()
{

    QString testFileName = QFileDialog::getOpenFileName(this, tr("Arquivo de Teste"), "/home/spades", "Text files (*.txt)");

    this->testFile = new QFile(testFileName);

}

void MainWindow::fileParse(QString fn)
{
    ui->statusBar->showMessage(fn);

    QFile file(fn);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erro",
                              "Ocorreu um erro ao abrir o arquivo",
                              QMessageBox::Ok);
        return;
    }

    QLabel *label = new QLabel("Processando. . .", this,  Qt::ToolTip);
    label->setStyleSheet("font: 75 20pt \"Arial\";background-color: white;");
    label->show();

    // Force the App to update the window and show the label
    QApplication::processEvents();

    QTextStream in(&file);

    // read the fist line. It contains the HEADERS
    QStringList first_line = in.readLine().split(",");
    ui->tableWidget->setColumnCount(first_line.length());
    ui->tableWidget->setHorizontalHeaderLabels(first_line);

    while (!in.atEnd()) {
        QStringList line_splited = in.readLine().split(",");

        int col = 0;
        int row = ui->tableWidget->rowCount();

        ui->tableWidget->insertRow(row);
        foreach (QString s, line_splited) {
            QTableWidgetItem *item = new QTableWidgetItem(s);
            ui->tableWidget->setItem(row, col++, item);
        }
    }

    emit tableUpdated();

    ui->tableWidget->item(2, 0)->setBackgroundColor(Qt::cyan);

    label->close();

    qDebug() << "Arquivo lido!";

    QFileInfo fi(file);
    QMessageBox::information(this,
                             "Arquivo carregado!",
                             "O arquivo \"" + fi.completeBaseName() +
                             "." +
                             fi.completeSuffix() +
                             "\" foi carregado!",
                             QMessageBox::Ok);
}

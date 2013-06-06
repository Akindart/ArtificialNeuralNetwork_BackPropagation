#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->tempList = new QHash<int, QList<double> >();

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

    // How to iterate over the hash
    /**
    QHashIterator<int, QList<double> > i(*tempList);
     while (i.hasNext()) {
         i.next();
         qDebug() << i.key() << ": " << i.value();
     }
     **/

    //this->traningFile = new QFile(file_name);

}

void MainWindow::on_actionAbrir_arquivo_de_teste_triggered()
{

    QString testFileName = QFileDialog::getOpenFileName(this, tr("Arquivo de Teste"), "", "Text files (*.txt)");

    //this->testFile = new QFile(testFileName);

}

void MainWindow::fileParse(QString fn)
{
    ui->statusBar->showMessage(fn);

    QFile file(fn);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erro",
                              "Ocorreu um erro ao abrir o arquivo",
                              QMessageBox::Ok);
        //return;
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

        normalize(row, line_splited);

        ui->tableWidget->insertRow(row);
        foreach (QString s, line_splited) {
            // add the line to table
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

void MainWindow::normalize(int key, QStringList l)
{
    /**
        X1, X2, X3, X4, X5, X6, classe
        1,  19, 35, 28, 17, 4,  1
    **/

    QList<double> list_double;
    QList<double> list_temp;

    // Min - Max of Line (l)
    for (int i = 0; i < l.size() - 1; i++)
        list_double.append(l.at(i).toDouble());

    qSort(list_double.begin(), list_double.end());

    qDebug() << list_double << "  " << list_double.first() << " " << list_double.last();

    double line_min = list_double.first();
    double line_max = list_double.last();

    // Update all of them...
    for (int i = 0; i < l.size() - 1; i++) {
        double v = l.at(i).toDouble();
        double v_new = (v - line_min) / (line_max - line_min);
        list_temp.append(v_new);
    }

    // Last element is the CLASS
    list_temp.append(l.last().toDouble());

    qDebug() << list_temp;
    tempList->insert(key, list_temp);
}

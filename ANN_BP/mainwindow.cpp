#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->tempList = new QHash<int, QList<double> >();
    this->testList = new QHash<int, QList<double> >();

    qtyInput = qtyHidden = qtyOutput = 0;

    lblProcessing = new QLabel("Processando. . .", this, Qt::ToolTip);
    lblProcessing->setStyleSheet("font: 75 20pt \"Arial\";background-color: white;");

    connect(this, SIGNAL(tableUpdated()), ui->tableWidget, SLOT(resizeColumnsToContents()));
    connect(this, SIGNAL(tableUpdated()), ui->tableConfusion, SLOT(resizeColumnsToContents()));
    connect(this, SIGNAL(tableUpdated()), ui->tableTest, SLOT(resizeColumnsToContents()));
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

    if (!file_name.isEmpty()) {
        fileParse(file_name);

        // execute training
        ui->grpCreateANN->setEnabled(true);
    }

}

void MainWindow::on_actionAbrir_arquivo_de_teste_triggered()
{

    QString testFileName = QFileDialog::getOpenFileName(this,
                                                        tr("Arquivo de Teste"),
                                                        "",
                                                     "CSV (*.csv);; TXT (*.txt)");

    if (!testFileName.isEmpty()) {
        fileTestParse(testFileName);
        // execute training
        ui->grpCreateANN->setEnabled(true);
    }
}

void MainWindow::fileParse(QString fn)
{
    ui->statusBar->showMessage(fn);

    QFile file(fn);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erro",
                              "Ocorreu um erro ao abrir o arquivo",
                              QMessageBox::Ok);
    }

    processing(true);

    QTextStream in(&file);

    // read the fist line. It contains the HEADERS
    QStringList first_line = in.readLine().split(",");
    ui->tableWidget->setColumnCount(first_line.length());
    ui->tableWidget->setHorizontalHeaderLabels(first_line);

    this->stringsToNormalize = new QList< QStringList >();

    while (!in.atEnd()) {
        QStringList line_splited = in.readLine().split(",");

        int col = 0;
        int row = ui->tableWidget->rowCount();

        this->stringsToNormalize->append(line_splited);

        ui->tableWidget->insertRow(row);
        foreach (QString s, line_splited) {
            // add the line to table
            QTableWidgetItem *item = new QTableWidgetItem(s);
            ui->tableWidget->setItem(row, col++, item);
        }
    }

    emit tableUpdated();

    processing(false);

    normalize();


    qDebug() << "Arquivo lido!";

    QFileInfo fi(file);
    QMessageBox::information(this,
                             "Arquivo carregado!",
                             "O arquivo \"" + fi.completeBaseName() +
                             "." +
                             fi.completeSuffix() +
                             "\" foi carregado!",
                             QMessageBox::Ok);

    calcLayers();
    updateTableNormalized();
}

void MainWindow::fileTestParse(QString fn)
{
    qDebug() << "fileTestParse";

    ui->statusBar->showMessage(fn);

    QFile file(fn);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erro",
                              "Ocorreu um erro ao abrir o arquivo",
                              QMessageBox::Ok);
    }

    processing(true);

    QTextStream in(&file);

    // read the fist line. It contains the HEADERS
    QStringList first_line = in.readLine().split(",");
    ui->tableTest->setColumnCount(first_line.length());
    ui->tableTest->setHorizontalHeaderLabels(first_line);

    this->stringsToNormalize = new QList< QStringList >();

    while (!in.atEnd()) {
        QStringList line_splited = in.readLine().split(",");

        int col = 0;
        int row = ui->tableTest->rowCount();

         this->stringsToNormalize->append(line_splited);

        ui->tableTest->insertRow(row);
        foreach (QString s, line_splited) {
            // add the line to table
            QTableWidgetItem *item = new QTableWidgetItem(s);
            ui->tableTest->setItem(row, col++, item);
        }
    }

    emit tableUpdated();

    processing(false);

    normalizeTest();

    qDebug() << "Arquivo lido!";

    QFileInfo fi(file);
    QMessageBox::information(this,
                             "Arquivo carregado!",
                             "O arquivo \"" + fi.completeBaseName() +
                             "." +
                             fi.completeSuffix() +
                             "\" foi carregado!",
                             QMessageBox::Ok);

    updateTestTableNormalized();
}

void MainWindow::normalize()
{
    /**
        X1, X2, X3, X4, X5, X6, classe
        1,  19, 35, 28, 17, 4,  1
    **/

    QList<double> maxs;
    QList<double> mins;

    for(int i=0; i<(this->stringsToNormalize->first().size()-1); i++){


        maxs.append(this->stringsToNormalize->first().at(i).toDouble());
        mins.append(this->stringsToNormalize->first().at(i).toDouble());

    }

    for(int i=0; i<this->stringsToNormalize->size(); i++){


        for(int j=0; j<(this->stringsToNormalize->at(i).size()-1); j++){

            if(maxs.at(j) < this->stringsToNormalize->at(i).at(j).toDouble())
                maxs.replace(j, this->stringsToNormalize->at(i).at(j).toDouble());

            else if(mins.at(j) > this->stringsToNormalize->at(i).at(j).toDouble())
                    mins.replace(j, this->stringsToNormalize->at(i).at(j).toDouble());

        }

    }

    for(int i=0; i<this->stringsToNormalize->size(); i++){

        QList<double> temp_List;

        for(int j=0; j<(this->stringsToNormalize->at(i).size()-1); j++){

            double newValue = (this->stringsToNormalize->at(i).at(j).toDouble() - mins.at(j))/(maxs.at(j)-mins.at(j));
            temp_List.append(newValue);

        }

        temp_List.append(this->stringsToNormalize->at(i).last().toDouble());

        //qDebug()<<temp_List.last();

        this->tempList->insert(i, temp_List);

    }
}

void MainWindow::normalizeTest()
{
    /**
        X1, X2, X3, X4, X5, X6, classe
        1,  19, 35, 28, 17, 4,  1
    **/

    QList<double> maxs;
    QList<double> mins;

    for(int i=0; i<(this->stringsToNormalize->first().size()-1); i++){


        maxs.append(this->stringsToNormalize->first().at(i).toDouble());
        mins.append(this->stringsToNormalize->first().at(i).toDouble());

    }

    for(int i=0; i<this->stringsToNormalize->size(); i++){


        for(int j=0; j<(this->stringsToNormalize->at(i).size()-1); j++){

            if(maxs.at(j) < this->stringsToNormalize->at(i).at(j).toDouble())
                maxs.replace(j, this->stringsToNormalize->at(i).at(j).toDouble());

            else if(mins.at(j) > this->stringsToNormalize->at(i).at(j).toDouble())
                    mins.replace(j, this->stringsToNormalize->at(i).at(j).toDouble());

        }

    }

    for(int i=0; i<this->stringsToNormalize->size(); i++){

        QList<double> temp_List;

        for(int j=0; j<(this->stringsToNormalize->at(i).size()-1); j++){

            double newValue = (this->stringsToNormalize->at(i).at(j).toDouble() - mins.at(j))/(maxs.at(j)-mins.at(j));
            temp_List.append(newValue);
            qDebug()<<"Valor de teste normalizado'"<<temp_List.last()<<"\n";

        }

        temp_List.append(this->stringsToNormalize->at(i).last().toDouble());

        this->testList->insert(i, temp_List);

    }

}

void MainWindow::updateTableNormalized()
{
    // "reset" the table
    ui->tableWidget->setRowCount(0);
    QHashIterator<int, QList<double> > i(*tempList);

    int row;

    while (i.hasNext()) {
        i.next();

        int col = 0;

        row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        foreach (double dv, i.value()) {
            // add the line to table
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(dv));
            ui->tableWidget->setItem(row, col++, item);
        }
    }

    emit tableUpdated();
}

void MainWindow::updateTestTableNormalized()
{
    // "reset" the table
    ui->tableTest->setRowCount(0);
    QHashIterator<int, QList<double> > i(*testList);

    int row;

    while (i.hasNext()) {
        i.next();

        int col = 0;

        row = ui->tableTest->rowCount();
        ui->tableTest->insertRow(row);

        foreach (double dv, i.value()) {
            // add the line to table
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(dv));
            ui->tableTest->setItem(row, col++, item);
        }
    }

    emit tableUpdated();
}

void MainWindow::updateConfusionMatrix()
{
    // "reset" the table
    ui->tableConfusion->setRowCount(0);

    // The Matrix
    QHash<int, QList<int> *> matrix = artificialNN->getConfusionMatrix()->getIndexes();
    // The Keys
    QList<int> matrix_keys = matrix.keys();

    QStringList keys_string;

    foreach(int i, matrix_keys)
        keys_string.append(QString::number(i));

    ui->tableConfusion->setColumnCount(keys_string.length());
    ui->tableConfusion->setHorizontalHeaderLabels(keys_string);

    QHashIterator<int, QList<int> *> i(matrix);
    while (i.hasNext()) {
        i.next();

        int col = 0;
        int row = ui->tableConfusion->rowCount();

        ui->tableConfusion->insertRow(row);

        QList<int> *matrix_values = i.value();
        foreach (int matrix_value, *matrix_values) {
            // add the line to table
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(matrix_value));
            ui->tableConfusion->setItem(row, col++, item);
        }
    }
    emit tableUpdated();
}

void MainWindow::calcLayers()
{
    QList<double> l_class;

    // Input Layer, amount of Neurons is the amount of COLs
    qtyInput = tempList->value(1).length() -1;

    QHashIterator<int, QList<double> > i(*tempList);
    while (i.hasNext()) {
        i.next();

        // get last element of line. It means the CLASS
        double last_element = i.value().last();

        if (!l_class.contains(last_element))
            l_class.append(last_element);
    }

     // Output Layer, amount of Neuros is th amount of CLASSes
     qtyOutput = l_class.length();
     qtyHidden = (int) sqrt(qtyInput * qtyOutput);

     ui->lblInputLayer->setText(QString("<html>Input: <b>" +
                                QString::number(qtyInput) +
                                "</b></html>"));
     ui->lblOutputLayer->setText(QString("<html>Output: <b>" +
                                QString::number(qtyOutput) +
                                "</b></html>"));
     ui->edtHiddenLayer->setText(QString::number(qtyHidden));
}

void MainWindow::saveConfusionMatrix()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Matriz de Confusao"),
                                                    "",
                                                    "CSV (*.csv)");

    if (fileName.isEmpty())
        return;

    QHash<int, QList<int> *> matrix = artificialNN->getConfusionMatrix()->getIndexes();

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        QMessageBox::critical(this, "Erro",
                              "Ocorreu um erro ao salvar o arquivo",
                              QMessageBox::Ok);
    }

    QTextStream out(&file);
    QList<int> matrix_keys = matrix.keys();

    QString keys_string = "# ";

    foreach(int i, matrix_keys)
        keys_string += QString::number(i) + ",";

    keys_string.remove(keys_string.length()-1, 1);

    out << keys_string + "\n";

    QHashIterator<int, QList<int> *> i(matrix);
    while (i.hasNext()) {
        i.next();

        QString values_string;

        QList<int> *matrix_values = i.value();
        foreach (int matrix_value, *matrix_values) {
            values_string += QString::number(matrix_value) + ",";
        }

        values_string.remove(values_string.length()-1, 1);

        out << QString::number(i.key()) << " " << values_string + "\n";
    }
}

void MainWindow::processing(bool b)
{
    if (b) {
        lblProcessing->show();
        ui->progressBar->setFormat("Processing. . .");
        ui->progressBar->setMaximum(0);
        QApplication::processEvents();
    }
    else {
        lblProcessing->close();
        ui->progressBar->setFormat("Done!");
        ui->progressBar->setMaximum(100);
        QApplication::processEvents();
    }

    // Force the App to update the window and show the label
    QApplication::processEvents();
}

void MainWindow::on_actionSalvar_matriz_de_confusao_triggered()
{
    saveConfusionMatrix();
}

void MainWindow::on_btnCreateNet_clicked()
{
    processing(true);

    artificialNN = new ANN_BP(this,
                              qtyInput,
                              qtyHidden,
                              qtyOutput);

    connect(artificialNN, SIGNAL(matrixUpdated()), this, SLOT(updateConfusionMatrix()));

    processing(false);

    // update groups
    ui->grpFunction->setEnabled(true);
    ui->grpStopCriteria->setEnabled(true);
    ui->btnTraining->setEnabled(true);
    ui->grpChangeWeights->setEnabled(true);
}

void MainWindow::on_btnTraining_clicked()
{
    qDebug() << ui->rdbLogistica->isChecked() << ", " <<
                ui->rdbErro->isChecked() << ", " <<
                ui->spinErro->text().toDouble() << ", " <<
                ui->spinMaxIteracoes->text().toInt();

    processing(true);

    artificialNN->exeANNBPLoopTraining(tempList,
                                       ui->rdbLogistica->isChecked(),
                                       ui->rdbErro->isChecked(),
                                       ui->spinErro->text().toDouble(),
                                       ui->spinMaxIteracoes->text().toInt());

    processing(false);

    ui->btnRunTest->setEnabled(true);

}

void MainWindow::on_btnRunTest_clicked()
{
    processing(true);

    artificialNN->exeANNBPLoopTest(testList,
                                   ui->rdbLogistica->isChecked());
    updateConfusionMatrix();

    processing(false);
}

void MainWindow::on_pushButton_clicked()
{
    qtyHidden = ui->edtHiddenLayer->text().toInt();
}

void MainWindow::on_cbbNeuronio_highlighted(const QString &arg1)
{
    QList<Neuron *> *list_neuron = NULL;

    ui->cbbPeso->clear();

    if (ui->cbbLayer->currentText() == "Input")
        list_neuron = artificialNN->getInputLayer();

    if (ui->cbbLayer->currentText() == "Hidden")
        list_neuron = artificialNN->getHiddenLayer();

    if (ui->cbbLayer->currentText() == "Output")
        list_neuron = artificialNN->getOutputLayer();

    for (int i = 1; i <= list_neuron->length(); i++)
        ui->cbbPeso->addItem(QString::number(i));
}

void MainWindow::on_cbbLayer_highlighted(const QString &arg1)
{
    ui->cbbNeuronio->clear();

    if (arg1 == "Input")
        for (int i = 1; i <= qtyInput; i++) {
            ui->cbbNeuronio->addItem(QString::number(i));
        }

    if (arg1 == "Hidden")
        for (int i = 1; i <= qtyHidden; i++) {
            ui->cbbNeuronio->addItem(QString::number(i));
        }

    if (arg1 == "Output")
        for (int i = 1; i <= qtyOutput; i++) {
            ui->cbbNeuronio->addItem(QString::number(i));
        }
}

void MainWindow::on_cbbPeso_highlighted(const QString &arg1)
{
    QList<Neuron *> *list_neuron = NULL;

    if (ui->cbbLayer->currentText() == "Input")
        list_neuron = artificialNN->getInputLayer();

    if (ui->cbbLayer->currentText() == "Hidden")
        list_neuron = artificialNN->getHiddenLayer();

    if (ui->cbbLayer->currentText() == "Output")
        list_neuron = artificialNN->getOutputLayer();

    double weight = list_neuron->at(ui->cbbNeuronio->currentIndex())->getWeights()->at(ui->cbbPeso->currentIndex());

    ui->edtWeight->setText(QString::number(weight));
}

void MainWindow::on_btnSetWeight_clicked()
{
    QList<Neuron *> *list_neuron = NULL;

    if (ui->cbbLayer->currentText() == "Input")
        list_neuron = artificialNN->getInputLayer();

    if (ui->cbbLayer->currentText() == "Hidden")
        list_neuron = artificialNN->getHiddenLayer();

    if (ui->cbbLayer->currentText() == "Output")
        list_neuron = artificialNN->getOutputLayer();

    for (int i = 1; i <= list_neuron->length(); i++)
        ui->cbbPeso->addItem(QString::number(i));

    list_neuron->at(ui->cbbNeuronio->currentIndex())->getWeights()->replace(ui->cbbPeso->currentIndex()-1,
                                                                            ui->edtWeight->text().toDouble());
}

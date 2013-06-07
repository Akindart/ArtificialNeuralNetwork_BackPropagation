#ifndef ANN_BP_H
#define ANN_BP_H

#include <QObject>
#include <neuron.h>
#include <QList>
#include <QString>
#include <random>
#include <QDebug>
#include "confusionmatrix.h"

class ANN_BP : public QObject
{
    Q_OBJECT
public:
    explicit ANN_BP(QObject *parent = 0);

    explicit ANN_BP(QObject *parent = 0, int qtyInputLayer = 1, int qtyHiddenLayer = 1, int qtyOutputLayer = 1);

    void exeANNBP(QList<double> inputValues, bool trainning, bool logistic); //executa para frente e faz o BP uma vez

    void setInputLayer(QList<Neuron *>  *inputLayer = new QList<Neuron *>);
    void setHiddenLayer(QList<Neuron *> *hiddenLayer = new QList<Neuron *>);
    void setOutputLayer(QList<Neuron *> *outputLayer = new QList<Neuron *>);
    void setN(double N);

    ConfusionMatrix *getConfusionMatrix();
    double getN();
    QList<Neuron *> *getInputLayer();
    QList<Neuron *> *getHiddenLayer();
    QList<Neuron *> *getOutputLayer();


private:

    QList<double> inputClass(double classExpected, int qtyOutPut);
    //QList<double> getInputClass(double &classExpected, int qtyOutPut);
    double randomDoubleNumber();

    double N;

    ConfusionMatrix *confMatrix;
    QList<Neuron *> *inputLayer;
    QList<Neuron *> *hiddenLayer;
    QList<Neuron *> *outputLayer;

signals:
    
public slots:
    
};

#endif // ANN_BP_H

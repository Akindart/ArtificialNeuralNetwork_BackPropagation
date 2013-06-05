#ifndef NEURON_H
#define NEURON_H

#include <QObject>
#include <QStringList>


#include <cmath>

class Neuron : public QObject
{
    Q_OBJECT
public:
    explicit Neuron(QObject *parent = 0);

    void setError(double error);
    void setOutputInformation(QString *outputInformation = new QString());
    void setInputInformation(QStringList *inputInformation = new QStringList());

    double getError();
    QString *getOutputInformation();
    QStringList *getInputInformation();


private:
    double calcTangHiperbolic(double n);
    double calcDerivTangHiperbolic(double n);
    double calcLogistic(double n);
    double calcDerivLogistic(double n);

    double error;

    QString *outputInformation; //neuronOrigin:valueOutput:destinyLayer
    QStringList *inputInformation;  //inputNumber:neurinOrigin:weight:value

signals:

public slots:

};

#endif // NEURON_H

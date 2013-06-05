#ifndef NEURON_H
#define NEURON_H

#include <QObject>

#include <cmath>

class Neuron : public QObject
{
    Q_OBJECT
public:
    explicit Neuron(QObject *parent = 0);

private:
    double calcTangHiperbolic(double n);
    double calcDerivTangHiperbolic(double n);
    double calcLogistic(double n);
    double calcDerivLogistic(double n);

signals:

public slots:

};

#endif // NEURON_H

#ifndef NEURON_H
#define NEURON_H

#include <QObject>
#include <QList>
#include <QString>
#include <cmath>
#include <QDebug>
#include <cmath>

class Neuron : public QObject
{
    Q_OBJECT
public:
    explicit Neuron(QObject *parent = 0, int id = 0);

    void calcOutputValue(QList<Neuron *> *Neurons, bool logistic);

    void setError(double error);
    void setNet(double net);
    void setId(int id);
    void setOutput(double output);
    void setWeights(QList<double> *weights);
    void setValues(QList<double> *values);
    void calcErrorOutputLayer(double expectedOutput, bool logistic);
    void calcErrorHiddenLayer(QList<Neuron *> *Neurons, bool logistic);
    void calcNewWeight(double N, QList<Neuron *> *Neurons);

    int getId();
    double getNet();
    double getError();
    double getOutput();
    QList<double> *getWeights();
    QList<double> *getValues();

private:
    double calcTangHiperbolic(double n);
    double calcDerivTangHiperbolic(double n);
    double calcLogistic(double n);
    double calcDerivLogistic(double n);
    void calcNet(QList<Neuron *> *Neurons);


    double error;
    double net;
    double output;

    int id;

    QList<double> *weights;
    QList<double> *values;




signals:

public slots:

};

#endif // NEURON_H

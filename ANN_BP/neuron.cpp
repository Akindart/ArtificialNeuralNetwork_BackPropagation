#include "neuron.h"

Neuron::Neuron(QObject *parent) :
    QObject(parent)
{
}

double Neuron::calcTangHiperbolic(double n)
{
    return ((1 - exp(-2*n)) / (1 + exp(-2*n)));
}

double Neuron::calcDerivTangHiperbolic(double n)
{
    return (1 - (calcTangHiperbolic(n) * calcTangHiperbolic(n)));
}

double Neuron::calcLogistic(double n)
{
    return (1 / (1 + exp(-n)));
}

double Neuron::calcDerivLogistic(double n)
{
    return ( exp(-n) / ((1 + exp(-n)) * (1 + exp(-n))) );
}

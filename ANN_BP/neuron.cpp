#include "neuron.h"


Neuron::Neuron(QObject *parent, int id):
    QObject(parent)
{

    this->id = id;
    this->weights = new QList<double>();

}

void Neuron::calcOutputValue(QList<Neuron *> *Neurons, bool logistic)
{

    this->calcNet(Neurons);

    if(logistic)
        this->setOutput(this->calcLogistic(this->getNet()));
    else  this->setOutput(this->calcTangHiperbolic(this->getNet()));

    //qDebug()<<this->getOutput()<<"\n";

}

double Neuron::calcTangHiperbolic(double n)
{
    return ((1.0 - (double)exp(-2*n)) / (1.0 + (double)exp(-2*n)));
}

double Neuron::calcDerivTangHiperbolic(double n)
{
    return (1 - (calcTangHiperbolic(n) * calcTangHiperbolic(n)));
}

double Neuron::calcLogistic(double n)
{
    return (double)(1.0 / (1.0 + (double)exp(-n)));
}

double Neuron::calcDerivLogistic(double n)
{
    return ( exp(-n) / ((1.0 + exp(-n)) * (1.0 + exp(-n))) );
}

void Neuron::calcErrorOutputLayer(double expectedOutput, bool logistic)
{
    double deriv;

    if(logistic)
        deriv = this->calcDerivLogistic(this->getNet());

    else deriv = this->calcDerivTangHiperbolic(this->getNet());

    this->setError(deriv*(expectedOutput - this->getOutput()));

    //qDebug()<<this->getId()<<" - "<<"Error: "<<this->getError()<<"\n";

}

void Neuron::


 calcErrorHiddenLayer(QList<Neuron *> *Neurons, bool logistic)
{

    double deriv;
    double tempSum = 0.0;

    if(logistic)
        deriv = this->calcDerivLogistic(this->getNet());

    else deriv = this->calcDerivTangHiperbolic(this->getNet());


    for(int i=0; i<Neurons->size(); i++){

        tempSum += (Neurons->at(i)->getError()*this->getWeights()->at(i));

    }

    this->setError(tempSum*deriv);

}

void Neuron::calcNewWeight(double N, QList<Neuron *> *Neurons)
{


    for(int i=0; i<this->getWeights()->size(); i++){

        this->getWeights()->insert(i, N*this->getError()*(Neurons->at(i)->getOutput()));
        this->getWeights()->removeAt(i+1);

    }


}

void Neuron::calcNet(QList<Neuron *> *Neurons)
{

    double tempSum = 0.0;

    for(int i=0; i<Neurons->size(); i++){

        tempSum = tempSum + (Neurons->at(i)->getOutput()*this->getWeights()->at(i));
        //qDebug()<<"Neurons->at("<<i<<")->getOutput()*this->getWeights()->at("<<i<<")"<<"\n";
        //qDebug()<<Neurons->at(i)->getOutput()<<"*"<<this->getWeights()->at(i)<<"\n";
        //qDebug()<<"Calculando net: neuronio "<<i<<"da camada anteiror com a a saida "<<Neurons->at(i)->getOutput()<<"\n";
        //qDebug()<<tempSum<<"\n";

    }

    this->setNet(tempSum);

}

void Neuron::setError(double error)
{

    this->error = error;

}

double Neuron::getError()
{

    return this->error;

}

double Neuron::getOutput()
{

    return this->output;

}

QList<double> *Neuron::getWeights()
{
    return this->weights;
}

QList<double> *Neuron::getValues()
{
    return this->values;

}

void Neuron::setNet(double net)
{

    this->net = net;

}

double Neuron::getNet()
{

    return this->net;

}

int Neuron::getId()
{

    return this->id;

}

void Neuron::setId(int id)
{

    this->id = id;

}

void Neuron::setOutput(double output)
{

    this->output = output;

}

void Neuron::setWeights(QList<double> *weights)
{

    this->weights = weights;
}

void Neuron::setValues(QList<double> *values)
{

    this->values = values;

}


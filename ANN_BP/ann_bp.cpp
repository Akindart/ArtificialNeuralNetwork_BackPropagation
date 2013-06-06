#include "ann_bp.h"
#include <math.h>

ANN_BP::ANN_BP(QObject *parent) :
    QObject(parent)
{



}

ANN_BP::ANN_BP(QObject *parent, int qtyInputLayer, int qtyHiddenLayer, int qtyOutputLayer) :
    QObject(parent)
{

    Neuron *tempNeuron;

    this->N = 0.01;

    for(int i=0; i<qtyInputLayer; i++){

        tempNeuron = new Neuron();

        tempNeuron->getWeights()->append(1.0);

        this->inputLayer->append(tempNeuron);

    }

    for(int i=0; i<qtyHiddenLayer; i++){

        tempNeuron = new Neuron();

        for(int i=0; i<qtyInputLayer; i++)
            tempNeuron->getWeights()->append(this->randomDoubleNumber());

        this->hiddenLayer->append(new Neuron());

    }

    for(int i=0; i<qtyOutputLayer; i++){

        for(int i=0; i<qtyHiddenLayer; i++)
            tempNeuron->getWeights()->append(this->randomDoubleNumber());

        this->outputLayer->append(new Neuron());

    }




}

void ANN_BP::exeANNBP(QList<double> inputValues)
{



}


double ANN_BP::randomDoubleNumber()
{

    double lower_bound = -1;
    double upper_bound = 1;
    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    std::default_random_engine re;
    double a_random_double = unif(re);

    return a_random_double;

}


void ANN_BP::setN(double N)
{

    this->N = N;

}

double ANN_BP::getN()
{

    return this->N;

}

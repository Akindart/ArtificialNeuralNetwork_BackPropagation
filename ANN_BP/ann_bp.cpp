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

void ANN_BP::exeANNBP(QList<double> inputValues, bool trainning, bool logistic)
{

    QList<double> howOutputShouldBe;

    howOutputShouldBe = this->inputClass(inputValues.last(), this->getOutputLayer()->size());

    int iterator = (inputValues.size()-1);

    for(int i=0; i<iterator; i++)
        this->getInputLayer()->at(i)->setOutput(inputValues.at(i));

    for(Neuron *tempNeuron : *this->getHiddenLayer())
       tempNeuron->calcOutputValue(this->getInputLayer());

    for(Neuron *tempNeuron : *this->getOutputLayer())
        tempNeuron->calcOutputValue(this->getHiddenLayer());

    if(trainning){

        for(int i=0; i<iterator; i++)
            this->getOutputLayer()->at(i)->calcErrorOutputLayer(howOutputShouldBe.at(i));

        for(Neuron *tempNeuron : *this->getHiddenLayer())
            tempNeuron->calcErrorHiddenLayer(this->getInputLayer()->size(), this->getOutputLayer());

        for(Neuron *tempNeuron : *this->getOutputLayer())
            tempNeuron->calcNewWeight(this->getN(), this->getHiddenLayer());

         for(Neuron *tempNeuron : *this->getOutputLayer())
             tempNeuron->calcNewWeight(this->getN(), this->getInputLayer());

    }
    else{



    }

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

QList<double> ANN_BP::inputClass(double &classExpected, int qtyOutPut)
{

    QList<double> *outputExpected = new QList<double>();

    for(int i=0; i<qtyOutPut; i++){

        if(i+1 == classExpected)
            outputExpected->append(1.0);
        else outputExpected->append(0.0);


    }

    return *outputExpected;

}

void ANN_BP::setN(double N)
{

    this->N = N;

}

double ANN_BP::getN()
{

    return this->N;

}

QList<Neuron *> *ANN_BP::getInputLayer()
{

    return this->inputLayer;

}

QList<Neuron *> *ANN_BP::getHiddenLayer()
{

    return this->hiddenLayer;

}

QList<Neuron *> *ANN_BP::getOutputLayer()
{

    return this->outputLayer;

}



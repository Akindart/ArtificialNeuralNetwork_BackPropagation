#include "ann_bp.h"
#include <math.h>

ANN_BP::ANN_BP(QObject *parent) :
    QObject(parent)
{



}

ANN_BP::ANN_BP(QObject *parent, int qtyInputLayer, int qtyHiddenLayer, int qtyOutputLayer) :
    QObject(parent)
{

    qDebug()<<"Input"<<qtyInputLayer<<"\n";
    qDebug()<<"Hidden"<<qtyHiddenLayer<<"\n";
    qDebug()<<"Output"<<qtyOutputLayer<<"\n";

    this->inputLayer = new QList<Neuron *>();
    this->hiddenLayer = new QList<Neuron *>();
    this->outputLayer = new QList<Neuron *>();

    Neuron *tempNeuron;
    this->N = 0.01;

    for(int i=0; i<qtyInputLayer; i++){

        tempNeuron = new Neuron(this, i);

        tempNeuron->getWeights()->append(1.0);

        this->inputLayer->append(tempNeuron);

        qDebug()<<tempNeuron->getId()<<"\n";

    }

    for(int i=0; i<qtyHiddenLayer; i++){

        tempNeuron = new Neuron(this, i);

        for(int j=0; j<qtyInputLayer; j++){
            tempNeuron->getWeights()->append(this->randomDoubleNumber());
            qDebug()<<"Peso "<<j<<" do neuronio: "<<i<<"da camada oculta: "<<tempNeuron->getWeights()->last()<<"\n";

        }
        this->hiddenLayer->append(tempNeuron);

        qDebug()<<tempNeuron->getId()<<"\n";

    }

    for(int i=0; i<qtyOutputLayer; i++){

        tempNeuron = new Neuron(this, i);

        for(int j=0; j<qtyHiddenLayer; j++)
            tempNeuron->getWeights()->append(this->randomDoubleNumber());

        this->outputLayer->append(tempNeuron);

        qDebug()<<tempNeuron->getId()<<"\n";

    }

    this->confMatrix = new ConfusionMatrix(this, qtyOutputLayer);


}

void ANN_BP::exeANNBP(QList<double> inputValues, bool trainning, bool logistic)
{

    QList<double> howOutputShouldBe;
    QList<double> outputs;

    howOutputShouldBe = this->inputClass(inputValues.last(), this->getOutputLayer()->size());

    int iterator = (inputValues.size()-1);

    for(int i=0; i<iterator; i++){
        this->getInputLayer()->at(i)->setOutput(inputValues.at(i));
        qDebug()<<"Neuronio de entrada "<<i<<"com saida "<<this->getInputLayer()->at(i)->getOutput()<<"\n";
    }
    for(Neuron *tempNeuron : *this->getHiddenLayer()){
        tempNeuron->calcOutputValue(this->getInputLayer(), logistic);
    }
    for(Neuron *tempNeuron : *this->getOutputLayer()){
        tempNeuron->calcOutputValue(this->getHiddenLayer(), logistic);
        outputs.append(tempNeuron->getOutput());
    }

    if(trainning){

        for(int i=0; i<iterator; i++)
            this->getOutputLayer()->at(i)->calcErrorOutputLayer(howOutputShouldBe.at(i), logistic);

        for(Neuron *tempNeuron : *this->getHiddenLayer())
            tempNeuron->calcErrorHiddenLayer(this->getInputLayer()->size(), this->getOutputLayer(), logistic);

        for(Neuron *tempNeuron : *this->getOutputLayer())
            tempNeuron->calcNewWeight(this->getN(), this->getHiddenLayer());

        for(Neuron *tempNeuron : *this->getOutputLayer())
             tempNeuron->calcNewWeight(this->getN(), this->getInputLayer());

    }

    else this->confMatrix->addMatrix(outputs, howOutputShouldBe);

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

QList<double> ANN_BP::inputClass(double classExpected, int qtyOutPut)
{

    QList<double> *outputExpected = new QList<double>();

    for(int i=0; i<qtyOutPut; i++){

        if(i+1 == classExpected)
            outputExpected->append(1.0);
        else outputExpected->append(0.0);

        qDebug()<<"Append: "<<outputExpected->last();

    }

    return *outputExpected;

}

void ANN_BP::setN(double N)
{

    this->N = N;

}

ConfusionMatrix *ANN_BP::getConfusionMatrix()
{

    return this->confMatrix;

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



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

    srand((unsigned)time(NULL));

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

void ANN_BP::exeANNBPLoopTraining(QHash<int, QList<double> > *tempList,
                                  bool logistic, bool error,
                                  double stopError, int qtyIterations)
{
    bool stop = true;



    if(error)
        while(stop){

            foreach(QList<double> inputString, *tempList){

                if(exeANNBP(inputString, true, logistic, error, stopError)==1) stop = false;

            }


        }
    else for(int i=0; i<qtyIterations; i++)
        foreach(QList<double> inputString, *tempList){

            exeANNBP(inputString, true, logistic, error, stopError);

        }



}

void ANN_BP::exeANNBPLoopTest(QHash<int, QList<double> > *tempList, bool logistic)
{

    foreach(QList<double> inputString, *tempList){

        exeANNBP(inputString, true, logistic, false, 0.0);

    }

}

int ANN_BP::exeANNBP(QList<double> inputValues, bool trainning, bool logistic, bool error, double stopError)
{

    QList<double> howOutputShouldBe;
    QList<double> outputs;

    double tempError = 0.0;

    howOutputShouldBe = this->inputClass(inputValues.last(), this->getOutputLayer()->size());

    int iterator = (inputValues.size()-1);

    for(int i=0; i<iterator; i++){
        this->getInputLayer()->at(i)->setOutput(inputValues.at(i));
        qDebug()<<"Neuronio de entrada "<<i<<"com saida "<<this->getInputLayer()->at(i)->getOutput()<<"\n";
    }
    for(Neuron *tempNeuron : *this->getHiddenLayer()){
        tempNeuron->calcOutputValue(this->getInputLayer(), logistic);
        qDebug()<<"Neuronio da camada oculta "<<tempNeuron->getId()<<"com saida "<<this->getHiddenLayer()->at(tempNeuron->getId())->getOutput()<<"\n";
    }
    for(Neuron *tempNeuron : *this->getOutputLayer()){
        tempNeuron->calcOutputValue(this->getHiddenLayer(), logistic);
        qDebug()<<"Neuronio de saida "<<tempNeuron->getId()<<"com saida "<<this->getOutputLayer()->at(tempNeuron->getId())->getOutput()<<"\n";
        outputs.append(tempNeuron->getOutput());
    }



    for(Neuron *tempNeuron : *this->getOutputLayer()){
        tempNeuron->calcErrorOutputLayer(howOutputShouldBe.at(tempNeuron->getId()), logistic);
        qDebug()<<"Saida esperada no neuronio "<<tempNeuron->getId()<<" da camada de saida: "<<howOutputShouldBe.at(tempNeuron->getId())<<"\n";
        tempError += (tempNeuron->getError()*tempNeuron->getError());

    }

    qDebug()<<"Net Error"<<this->calcANNBPError(tempError)<<"\n";

    if(error && (this->calcANNBPError(tempError) < stopError)) return 1;


    for(Neuron *tempNeuron : *this->getHiddenLayer()){
        tempNeuron->calcErrorHiddenLayer(this->getOutputLayer(), logistic);
        qDebug()<<"Error do neuronio "<<tempNeuron->getId()<<" da camada oculta: "<<tempNeuron->getError()<<"\n";
    }

    if(trainning){

        for(Neuron *tempNeuron : *this->getOutputLayer()){
            tempNeuron->calcNewWeight(this->getN(), this->getHiddenLayer());
        }

        for(Neuron *tempNeuron : *this->getHiddenLayer()){
            tempNeuron->calcNewWeight(this->getN(), this->getInputLayer());
        }

    }

    else this->confMatrix->addMatrix(outputs, howOutputShouldBe);


    emit matrixUpdated();

    return 0;

}


double ANN_BP::randomDoubleNumber()
{

    return (-1) + ((double)rand()/(double)RAND_MAX) * (2);

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

double ANN_BP::calcANNBPError(double sumOutputError)
{

    return (0.5)*sumOutputError;

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



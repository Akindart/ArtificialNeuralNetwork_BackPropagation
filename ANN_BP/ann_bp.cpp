#include "ann_bp.h"

ANN_BP::ANN_BP(QObject *parent) :
    QObject(parent)
{



}

ANN_BP::ANN_BP(QObject *parent, int qtyInputLayer, int qtyHiddenLayer, int qtyOutputLayer) :
    QObject(parent)
{

    for(int i=0; i<qtyInputLayer; i++){

        //this->inputLayer->append(new Neuron());

    }

}

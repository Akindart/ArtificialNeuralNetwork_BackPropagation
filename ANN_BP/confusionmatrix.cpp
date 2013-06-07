#include "confusionmatrix.h"

ConfusionMatrix::ConfusionMatrix(QObject *parent, int qtyClasses) :
    QObject(parent)
{

    for(int i=0; i<qtyClasses; i++){

        QList<int> *tempList = new QList<int>();

        for(int j=0; j<qtyClasses; j++){
            tempList->append(0);
            qDebug()<<"Criaçao ConfusionMatrix: Ultimo item inserto na lista: "<<tempList->last()<<"Lista: "<<i<<"\n";
        }

        this->indexes.insert(i+1, new QList<int>());


    }

}

void ConfusionMatrix::addMatrix(QList<double> outputs, QList<double> howOutputShouldBe)
{
    int MaxOut = 0, MaxExpected = 0;
    double valueMax = outputs.first();

    for(int i=1; i<outputs.size(); i++){

        if(valueMax < outputs.at(i)){

            valueMax = outputs.at(i);
            MaxOut = i;

        }
        if(howOutputShouldBe.at(i) == 1){

            MaxExpected = i;

        }

    }

    int tempValue = this->indexes.value(MaxExpected+1)->at(MaxOut) + 1;
    this->indexes.value(MaxExpected+1)->replace(MaxOut, tempValue);

}

QHash<int, QList<int> *> ConfusionMatrix::getIndexes()
{
    return this->indexes;
}

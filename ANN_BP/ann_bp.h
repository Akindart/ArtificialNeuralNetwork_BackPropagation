#ifndef ANN_BP_H
#define ANN_BP_H

#include <QObject>
#include <neuron.h>

class ANN_BP : public QObject
{
    Q_OBJECT
public:
    explicit ANN_BP(QObject *parent = 0);
    
private:

    QList<Neuron> *inputLayer;

signals:
    
public slots:
    
};

#endif // ANN_BP_H

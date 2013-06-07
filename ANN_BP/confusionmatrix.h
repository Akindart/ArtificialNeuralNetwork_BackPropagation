#ifndef CONFUSIONMATRIX_H
#define CONFUSIONMATRIX_H

#include <QObject>
#include <QHash>

class ConfusionMatrix : public QObject
{
    Q_OBJECT
public:
    explicit ConfusionMatrix(QObject *parent = 0, int qtyClasses = 0);
    void addClasses(QList<int> &classe);
    void addMatrix(QList<double> outputs, QList<double> howOutputShouldBe);



    QHash<int, QList<int> *> getIndexes();

private:

    QHash<int, QList<int> *> indexes;
    
signals:
    
public slots:
    
};

#endif // CONFUSIONMATRIX_H

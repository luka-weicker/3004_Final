#include "Organ.h"

Organ::Organ(QString _name)
{
    name = _name;
}

void Organ::addData(int _dataPoint){
    results.append(_dataPoint);
}

int Organ::getData(int _dataSlot){
    return results.at(_dataSlot);
}

int Organ::getDataLast(){
    return results.last();
}

void Organ::printAllResults(){
    qDebug().noquote().nospace() << name << ": ";
    for (int i=0; i<results.length(); i++){
        qDebug() << " " << results.at(i);
    }
}

void Organ::printLastResult(){
    qDebug().noquote().nospace() << name << ": \t" << this->getDataLast();
}

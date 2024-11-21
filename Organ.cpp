#include "Organ.h"

Organ::Organ(QString name)
{
    this->name = name;
}

void Organ::addData(int _dataPoint){
    results.append(_dataPoint);
}

int Organ::getData(int _dataSlot){
    return results.at(_dataSlot);
}


float Organ::getAverage(){
    float runningTotal = 0.0;
    for (int i=0; i<results.length(); i++){
        runningTotal  += results.at(i);
    }
    return (runningTotal / results.length());
}

#include "Organ.h"

Organ::Organ(QString name)
{
    this->name = name;
}

Organ::~Organ(){

}

float Organ::getAverage(){
    float runningTotal = 0.0;
    for (int i=0; i<results.length(); i++){
        runningTotal  += results.at(i);
    }
    return (runningTotal / results.length());
}

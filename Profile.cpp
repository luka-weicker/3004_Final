#include "Profile.h"

Profile::Profile(QString _name)
{
    name = _name;
    totalScans = 0;

    QString organNames[] = {"Heart", "Lungs", "Liver", "Kidney", "Stomach"};

    for (int i=0; i<NUM_ORGANS; i++){
        organs[i] = new Organ(organNames[i]);
    }
}

Profile::~Profile(){

}



void Profile::generateResults(){
    int v;
    for (int i = 0; i<NUM_ORGANS; i++){
        v = QRandomGenerator::global()->bounded(100);
        inputResult(i, v);
    }
    totalScans++;
}

void Profile::inputResult(int _organSlot, int _v){
    organs[_organSlot]->addData(_v);
}

void Profile::printAllResults(){
    for (int i=0; i<NUM_ORGANS; i++){organs[i]->printAllResults();}
}

void Profile::printLastResults()   {
    for (int i=0; i<NUM_ORGANS; i++){organs[i]->printLastResult();}
}

void Profile::printProfile(int _profileSlot){
    qDebug().noquote().nospace() << _profileSlot << ". "<< name <<" has "<< totalScans<<" scans";
}

void Profile::printOrganResults(QString _organName){
    for (int i=0; i<NUM_ORGANS; i++){
        if (organs[i]->getName() == _organName){
            organs[i]->printAllResults();
        }
    }
}

void Profile::printAverageResults()   {
    QString organName;
    for (int i=0; i<NUM_ORGANS; i++){
        organName = organs[i]->getName();
        qDebug().noquote().nospace() << organName <<": \t"<<organs[i]->getAverage();
    }
}

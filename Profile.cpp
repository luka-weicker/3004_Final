#include "Profile.h"

Profile::Profile(QString _name)
{
    name = _name;
    totalScans = 0;

    QString organNames[] = {"Heart", "Lungs", "Liver", "Kidney", "Spleen", "Stomach",
    "Large Intestine", "Small Intestine", "Bladder", "Gallbladder", "Pancreas", "Adrenal Glands"};

    for (int i=0; i<NUM_ORGANS; i++){
        organs[i] = new Organ(organNames[i]);
    }
}

Profile::~Profile(){

}

void Profile::generateResults(){
    int v;
    for (int i = 0; i<NUM_ORGANS; i++){
        v = QRandomGenerator::global()->bounded(300);
        organs[i]->addData(v);
    }
    totalScans++;
}

void Profile::printAllResults(){
    //for (int i=0; i<NUM_ORGANS; i++){organs[i]->printAllResults();}
    for (int i = 0; i < NUM_ORGANS; i++){
        for (int j = 0; j < organs[i]->getResultsLength(); j++){
            qInfo().noquote().nospace() << organs[i]->getName() << ": " << organs[i]->getData(j);
        }
    }
}

void Profile::printLastResults(){
    for (int i=0; i<NUM_ORGANS; i++){
        qInfo().noquote().nospace() << organs[i]->getName() << ": " <<organs[i]->getDataLast();
    }
}

void Profile::printProfile(int _profileSlot){
    qDebug().noquote().nospace() << _profileSlot << ". "<< name <<" has "<< totalScans<<" scans";
}

void Profile::printOrganResults(QString _organName){
    for (int i=0; i<NUM_ORGANS; i++){
        if (organs[i]->getName() == _organName){
            for (int j = 0; j < organs[i]->getResultsLength(); j++){
                qInfo().noquote().nospace() << organs[i]->getName() << ": " << organs[i]->getData(j);
            }
        }
    }
}

void Profile::printAverageResults()   {
    for (int i=0; i<NUM_ORGANS; i++){
        qDebug().noquote().nospace() << organs[i]->getName() << ": \t"<<organs[i]->getAverage();
    }
}

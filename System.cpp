#include "System.h"

System::System()
{
    totalProfiles = 0;
    selectedProfileSlot=0;
}

System::~System(){

}

void System::generateResults(int _profileSlot){
    profiles[_profileSlot]->generateResults();
}

bool System::newProfile(QString _name){
    if (totalProfiles >= MAX_PROFILES){
        qDebug().noquote().nospace() << "You already have "<<MAX_PROFILES<<" profiles, that is the max";
        totalProfiles++;
        return false;
    }
    else{

        if (_name  == ""){
            qDebug()<<"You cannot enter a blank name";
            return false;
        }

        // Check if the name is already used
        for (int i=0; i<profiles.length(); i++){
            if (_name == profiles[i]->getName()){
                qDebug()<<"This name is already in use, please use another name";
                return false;
            }
        }


        profiles.append(new Profile(_name));
        totalProfiles++;
        qDebug() << "Created a new user with name "<<_name;
    }
    return true;
}

void System::printAllResults(int _profileSlot){
    profiles[_profileSlot]->printAllResults();
}

void System::printLastResults(int _profileSlot){
    profiles[_profileSlot]->printLastResults();
}



void System::printProfiles(){
    for (int i=0; i<profiles.length();  i++){
        profiles.at(i)->printProfile(i);
    }
}

void System::printOrganResults(int _profileSlot, QString _organName){
    profiles[_profileSlot]->printOrganResults(_organName);
}

void System::printAverageResults(int _profileSlot){
    profiles[_profileSlot]->printAverageResults();
}

#include "System.h"

System::System()
{
    totalProfiles = 0;
    selectedProfileSlot=0;
    profiles.append(new Profile("Bob"));
}

System::~System(){

}

void System::generateResults(int _profileSlot){
    profiles[_profileSlot]->generateResults();
}

void System::newProfile(QString _name){
    if (totalProfiles >= 5){return;}
    else{
        profiles.append(new Profile(_name));
        totalProfiles++;
        qDebug() << "Created a new user with name "<<_name;
    }
}

void System::printAllResults(int _profileSlot){
    profiles[_profileSlot]->printAllResults();
}

void System::printLastResults(int _profileSlot){
    profiles[_profileSlot]->printLastResults();
}



void System::printProfiles(){
    qDebug() << "Here are all of the profiles:  ";
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

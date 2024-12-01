#include "System.h"

System::System()
{
    totalProfiles = 0;
    selectedProfileSlot=0;
    loadProfiles();
}

System::~System(){
    for (int i =0; i < profiles.size(); i++){
        delete profiles.at(i);
    }
}

void System::generateResults(int _profileSlot){
    profiles[_profileSlot]->generateResults();
    saveProfiles();
}

bool System::newProfile(QString _name){

    // Check if profiles are maxed
    if (totalProfiles >= MAX_PROFILES){
        qDebug().noquote().nospace() << "You already have "<<MAX_PROFILES<<" profiles, that is the max";
        return false;
    }

    // Check if name is blank
    if (_name  == ""){
        qDebug()<<"Please enter a profile name.";
        return false;
    }

    // Check if the name is already used
    for (int i=0; i<profiles.length(); i++){
        if (_name == profiles[i]->getName()){
             qDebug()<<"This name is already in use, please use another name";
             return false;
        }
    }

    // Add if new user is valid
    Profile *newProfile = new Profile(_name);
    profiles.append(newProfile);
    totalProfiles++;
    saveProfiles();
    return true;
}

bool System::deleteProfile(int profileSlot)
{
    // Check if the profileSlot is valid
    if (profileSlot < 0 || profileSlot >= profiles.size()) {
        qDebug() << "Invalid profile selection. Cannot delete.";
        return false;
    }

    // Get the name of the profile before deletion for logging
    QString deletedProfileName = profiles[profileSlot]->getName();

    // Free the memory allocated for the profile
    delete profiles[profileSlot];

    // Remove the profile from the vector
    profiles.removeAt(profileSlot);
    totalProfiles--;

    // Adjust selectedProfileSlot if necessary
    if (totalProfiles == 0) {
        selectedProfileSlot = -1; // No profiles left
    } else if (profileSlot <= selectedProfileSlot) {
        selectedProfileSlot = (selectedProfileSlot == 0) ? 0 : selectedProfileSlot - 1; // Adjust index
    }

    // Save the updated profiles to the JSON file
    saveProfiles();

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

void System::analyzeHealthResults(int _profileSlot){
    profiles[_profileSlot]->analyzeHealthResults();
}

void System::loadProfiles()
{
    QJsonDocument doc = FileHandler::readJson("profiles.json");
    if (doc.isNull() || !doc.isArray()) {
        qDebug() << "No profiles found or invalid format.";
        return;
    }

    //creating new profiles based on json file upon application loading
    QJsonArray profilesArray = doc.array();
    for (const QJsonValue &value : profilesArray) {
        QJsonObject profileJson = value.toObject();
        Profile *profile = new Profile();
        profile->fromJson(profileJson);
        profiles.append(profile);
        totalProfiles++;
    }
}

void System::saveProfiles()
{
    QJsonArray profilesArray;
    for (Profile *profile : profiles) {
        profilesArray.append(profile->toJson());
    }
    QJsonDocument doc(profilesArray);
    //qDebug() << "Current working directory:" << QDir::currentPath(); FOR TESTING
    FileHandler::writeJson("profiles.json", doc);
}

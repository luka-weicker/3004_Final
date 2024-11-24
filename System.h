#ifndef SYSTEM_H
#define SYSTEM_H

#include <QString>
#include "Profile.h"
#include <QVector>
#include "filehandler.h"

class System
{
    public:
        // Constructors & destructors
        System();
        ~System();

        // Funcctionality
        void generateResults(int _profileSlot);
        bool newProfile(QString _name="no_profile_name");
        bool deleteProfile(int profileSlot);

        // Printing
        void printAllResults(int _profileSlot);
        void printLastResults(int _profileSlot);
        void printProfiles();
        void printOrganResults(int _profileSlot, QString _organName);

        void analyzeHealthResults(int _profileSlot);

        // Persistence
        void loadProfiles();
        void saveProfiles();

        // Getters & setters
        inline int getSelectedProfileSlot() { return selectedProfileSlot; }
        inline QString getCurrentProfileName() { return profiles[selectedProfileSlot]->getName(); }
        inline int getTotalProfiles() { return totalProfiles; }
        inline int getSelectedProfileTotalScans() { return profiles[selectedProfileSlot]->getTotalScans(); }
        inline QVector<Profile *> getProfiles() { return profiles; }

        inline int getProfileEnergy(int profileSlot){return profiles[selectedProfileSlot]->getEnergy();}
        inline int getProfileIS(int profileSlot){return profiles[selectedProfileSlot]->getIS();}
        inline int getProfileMetabolism(int profileSlot){return profiles[selectedProfileSlot]->getMetabolism();}
        inline int getProfilePsycho(int profileSlot){return profiles[selectedProfileSlot]->getPsycho();}
        inline int getProfileMusc(int profileSlot){return profiles[selectedProfileSlot]->getMusc();}

        inline void setSelectedProfileSlot(int _newSlot) { selectedProfileSlot = _newSlot; }

    private:
        int selectedProfileSlot;
        int totalProfiles;
        QVector<Profile*> profiles;
};

#endif // SYSTEM_H

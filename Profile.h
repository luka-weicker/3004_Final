#ifndef PROFILE_H
#define PROFILE_H

#include <QString>
#include "Organ.h"
#include <QRandomGenerator>
#include "defs.h"

class Profile
{
    public:
        // Constructors & destructors
        Profile(QString _name="no_profile_name");
        ~Profile();

        // Fucntionality
        void generateResults();

        // Printing
        void printAllResults();
        void printLastResults();
        void printProfile(int _profileSlot);
        void printOrganResults(QString _organName);
        void printAverageResults();

        // Getters & setters
        inline QString getName(){return name;}
        inline int getTotalScans() {return totalScans;}

    private:
        QString name;
        int totalScans;
        Organ* organs[NUM_ORGANS];
};

#endif // PROFILE_H

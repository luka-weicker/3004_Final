#ifndef PROFILE_H
#define PROFILE_H

#include <QString>
#include <QMap>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include "defs.h"

class Profile
{
    public:
        // Constructors & destructors
        Profile(QString _name="no_profile_name");
        ~Profile();

        // Fucntionality
        void generateResults();                                 // Generate a round of results for all organs
        bool addToSpecificOrgan(QString _organ, int _value);    // Add data to one organ by name (returns true if organ is found)

        // Printing
        void printAllResults();
        void printLastResults();
        void printProfile(int _profileSlot);
        void printOrganResults(QString _organName);
        void printAverageResults();

        //json
        QJsonObject toJson() const;
        void fromJson(const QJsonObject &json);

        // Getters & setters
        inline QString getName(){return name;}
        inline int getTotalScans() {return totalScans;}

    private:
        QString name;
        int totalScans;
        QMap<QString, QVector<int>> organData;
        //Organ* organs[NUM_ORGANS];
};

#endif // PROFILE_H

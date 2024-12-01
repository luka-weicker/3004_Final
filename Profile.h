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
        void generateResults();
        bool addToSpecificOrgan(QString _organ, int _value);
        int getLatestOrganValue(const QString &organName);

        // Printing
        void printAllResults();
        void printLastResults();
        void printProfile(int _profileSlot);
        void printOrganResults(QString _organName);
        void analyzeHealthResults();

        //json
        QJsonObject toJson() const;
        void fromJson(const QJsonObject &json);

        // Getters & setters
        inline QString getName(){return name;}
        inline int getTotalScans() {return totalScans;}
        inline int getEnergy(){return energy_level;}
        inline int getIS(){return immune_system_level;}
        inline int getMetabolism(){return metabolism_level;}
        inline int getPsycho(){return psycho_emotional_level;}
        inline int getMusc(){return musculoskeletal_level;}


    private:
        QString name;
        int totalScans;
        QMap<QString, QVector<int>> organData;

        //used for analysis
        int energy_level;
        int immune_system_level;
        int metabolism_level;
        int psycho_emotional_level;
        int musculoskeletal_level;
};

#endif

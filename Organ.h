#ifndef ORGAN_H
#define ORGAN_H

#include <QString>
#include <QVector>
#include <QDebug>

class Organ
{
    public:
        // Constructor and destructor
        Organ(QString _name="no_organ_name");
        ~Organ();

        // Functionality
        inline void addData(int _dataPoint) {results.append(_dataPoint);}               // Add data value to results vector

        // Getters and setters
        inline int getData(int _dataSlot) {return results.at(_dataSlot);}
        inline int getDataLast() {return results.last();}
        inline QString getName(){return name;}
        float getAverage();
        inline int getResultsLength(){return results.size();}

    private:
        QString name;
        QVector<int> results;
};

#endif // ORGAN_H

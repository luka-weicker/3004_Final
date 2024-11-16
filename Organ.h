#ifndef ORGAN_H
#define ORGAN_H

#include <QString>
#include <QVector>
#include <QDebug>

class Organ
{
    public:
        Organ(QString _name="no_organ_name");
        ~Organ();

        void addData(int _dataPoint);
        int getData(int _dataSlot);
        int getDataLast();            // i think this can be removed with a default val to getData
        void printAllResults();
        void printLastResult();
        inline QString getName(){return name;}

    private:
        QString name;
        QVector<int> results;
};

#endif // ORGAN_H

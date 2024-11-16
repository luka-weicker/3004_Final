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
        int getDataLast();
        void printAllResults();
        void printLastResult();

        inline QString getName(){return name;}
        float getAverage();

    private:
        QString name;
        QVector<int> results;
};

#endif // ORGAN_H

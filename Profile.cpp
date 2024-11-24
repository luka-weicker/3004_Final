#include "Profile.h"
#include <QRandomGenerator>
#include <QDebug>

Profile::Profile(QString _name)
{
    name = _name;
    totalScans = 0;

    QString organNames[] = {"Heart", "Lungs", "Liver", "Kidney", "Spleen", "Stomach",
    "Large Intestine", "Small Intestine", "Bladder", "Gallbladder", "Pancreas", "Adrenal Glands"};

    for (const QString &organName : organNames) {
        organData[organName] = QVector<int>();
    }
}

Profile::~Profile(){

}

void Profile::generateResults(){
    for (auto &dataVector : organData) {
        int v = QRandomGenerator::global()->bounded(300);
        dataVector.append(v);
    }
    totalScans++;
}

bool Profile::addToSpecificOrgan(QString _organ, int _value){
    if (organData.contains(_organ)) {
        organData[_organ].append(_value);
        return true;
    }
    return false;
}

void Profile::printAllResults(){
    for (auto it = organData.begin(); it != organData.end(); ++it) {
        for (int value : it.value()) {
            qInfo().noquote().nospace() << it.key() << ": " << value;
        }
    }
}

void Profile::printLastResults(){
    for (auto it = organData.begin(); it != organData.end(); ++it) {
        if (!it.value().isEmpty()) {
            qInfo().noquote().nospace() << it.key() << ": " << it.value().last();
        }
    }
}

void Profile::printProfile(int _profileSlot){
    qDebug().noquote().nospace() << _profileSlot << ". "<< name <<" has "<< totalScans<<" scans";
}

void Profile::printOrganResults(QString _organName){
    if (organData.contains(_organName)) {
        for (int value : organData[_organName]) {
            qInfo().noquote().nospace() << _organName << ": " << value;
        }
    } else {
        qDebug() << "Organ not found.";
    }
}

void Profile::printAverageResults()   {
    for (auto it = organData.begin(); it != organData.end(); ++it) {
        double sum = 0;
        for (int value : it.value()) {
            sum += value;
        }
        double average = it.value().isEmpty() ? 0 : sum / it.value().size();
        qDebug().noquote().nospace() << it.key() << ": \t" << average;
    }
}

QJsonObject Profile::toJson() const
{
    QJsonObject json;
    json["name"] = name;
    json["totalScans"] = totalScans;

    QJsonObject organsJson;
    for (auto it = organData.begin(); it != organData.end(); ++it) {
        QJsonArray dataArray;
        for (int value : it.value()) {
            dataArray.append(value);
        }
        organsJson[it.key()] = dataArray;
    }
    json["organData"] = organsJson;
    return json;
}

void Profile::fromJson(const QJsonObject &json)
{
    name = json["name"].toString();
    totalScans = json["totalScans"].toInt();

    organData.clear();
    QJsonObject organsJson = json["organData"].toObject();
    for (auto it = organsJson.begin(); it != organsJson.end(); ++it) {
        QJsonArray dataArray = it.value().toArray();
        QVector<int> dataVector;
        for (const QJsonValue &value : dataArray) {
            dataVector.append(value.toInt());
        }
        organData[it.key()] = dataVector;
    }
}

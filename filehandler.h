#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

class FileHandler {
public:
    static QJsonDocument readJson(const QString &filePath);
    static bool writeJson(const QString &filePath, const QJsonDocument &doc);
};

#endif

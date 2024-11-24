#include "filehandler.h"

QJsonDocument FileHandler::readJson(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading:" << filePath;
        return QJsonDocument();
    }

    QByteArray data = file.readAll();
    file.close();
    return QJsonDocument::fromJson(data);
}

bool FileHandler::writeJson(const QString &filePath, const QJsonDocument &doc) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << filePath;
        return false;
    }

    file.write(doc.toJson());
    file.close();
    return true;
}

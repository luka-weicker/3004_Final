#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>

class DatabaseManager {
public:
    static DatabaseManager& instance();
    bool connectToDatabase(const QString &dbPath = "data/profiles.sqlite");

    QSqlDatabase getDatabase() const { return db; }

private:
    DatabaseManager() = default;                 // Private constructor
    ~DatabaseManager() = default;                // Private destructor
    DatabaseManager(const DatabaseManager&) = delete;            // No copy
    DatabaseManager& operator=(const DatabaseManager&) = delete; // No assignment

    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H

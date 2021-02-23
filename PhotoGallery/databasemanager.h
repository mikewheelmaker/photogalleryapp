#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QLoggingCategory>

#include "utilities.h"

Q_DECLARE_LOGGING_CATEGORY(databaseManager)

const QString CREATE_TABLE("CREATE TABLE IF NOT EXISTS %1 (%2)");

class DatabaseManager
{
public:
    enum SearchCategories {
        FileName = 0,
        Width,
        Height,
        Size
    };

public:
    DatabaseManager(const QString &path);
    ~DatabaseManager();

    bool createTable();
    bool insertPhoto(const PhotoInformation &info);
    bool selectPhoto(const PhotoInformation &info, SearchCategories category);
    bool deletePhoto(const PhotoInformation &info, SearchCategories category);
    bool dropTable(const QString &tableName);
    QList<PhotoInformation> getDbContent(const QString &tableName);

private:
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include "databasemanager.h"

Q_LOGGING_CATEGORY(databaseManager, "databaseManager.log")

DatabaseManager::DatabaseManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if(!m_db.open())
    {
        qCDebug(databaseManager, "\n\t\t\t[DatabaseManager] Constructor called --- connection with database failed");
        //qDebug() << "DatabaseManager Constructor: connection with database failed";
    }
    else
    {
        qCDebug(databaseManager, "\n\t\t\t[DatabaseManager] Constructor called --- connection established successfully");
        //qDebug() << "DatabaseManager Constructor: connection established successfully";
    }
}

DatabaseManager::~DatabaseManager()
{
    qCDebug(databaseManager, "\n\t\t\t[DatabaseManager] Destructor called");
    if(m_db.isOpen())
    {
        m_db.close();
    }
}

bool DatabaseManager::createTable()
{
    QSqlQuery query;
    QString sql(CREATE_TABLE.arg("photos", "ids integer primary key, fileURL text, filePath text, thumbnailURL text, fileName text, width integer, height integer, size integer"));

    if(!query.exec(sql))
    {
        qCDebug(databaseManager) << "\n\t\t\t[DatabaseManager] Error on creating table: " << query.lastError();
        //qDebug() << "createTable: error on running " << query.lastError();
        return false;
    }
    else
    {
        qCDebug(databaseManager) << "\n\t\t\t[DatabaseManager] Table created successfully";
        //qDebug() << "createTable: success";
    }

    return true;
}

bool DatabaseManager::insertPhoto(const PhotoInformation &info)
{
    bool success = false;

    QSqlQuery query;
    query.prepare("INSERT INTO photos (fileURL, filePath, thumbnailURL, fileName, width, height, size) VALUES (:fileURL, :filePath, :thumbnailURL, :fileName, :width, :height, :size)");
    query.bindValue(":fileURL", info.fileURL);
    query.bindValue(":filePath", info.filePath);
    query.bindValue(":thumbnailURL", info.fileThumbnailURL);
    query.bindValue(":fileName", info.fileName);
    query.bindValue(":width", info.width);
    query.bindValue(":height", info.height);
    query.bindValue(":size", info.sizeInBytes);

    if(!selectPhoto(info, FileName))
    {
        if(query.exec())
        {
            qCDebug(databaseManager) << "\n\t\t\t[DatabaseManager] Photo inserted successfully";
            //qDebug() << "insertPhoto: photo inserted successfully";
            success = true;
        }
        else
        {
            qCDebug(databaseManager) << "\n\t\t\t[DatabaseManager] Error when inserting photo: " << query.lastError();
            //qDebug() << "insertPhoto: error " << query.lastError();
        }
    }
    else
    {
        qCDebug(databaseManager) << "\n\t\t\t[DatabaseManager] Cannot insert photo: already in database";
        //qDebug() << "insertPhoto: photo already in database";
    }

    return success;
}

bool DatabaseManager::selectPhoto(const PhotoInformation &info, DatabaseManager::SearchCategories category)
{
    QSqlQuery query;

    switch(category)
    {
    case FileName:
        query.prepare("SELECT fileName FROM photos WHERE fileName = (:fileName)");
        query.bindValue(":fileName", info.fileName);
        break;
    case Width:
        query.prepare("SELECT width FROM photos WHERE width = (:width)");
        query.bindValue(":width", info.width);
        break;
    case Height:
        query.prepare("SELECT height FROM photos WHERE height = (:height)");
        query.bindValue(":height", info.height);
        break;
    case Size:
        query.prepare("SELECT size FROM photos WHERE size = (:size)");
        query.bindValue(":size", info.sizeInBytes);
        break;
    default:
        query.prepare("SELECT fileName FROM photos WHERE fileName = (:fileName)");
        query.bindValue(":fileName", info.fileName);
        break;
    }

    if(!query.exec())
    {
        qCDebug(databaseManager) << "\n\t\t\t[DatabaseManager] Error finding photo: " << query.lastError();
        //qDebug() << "selectPhoto: error" << query.lastError();
    }
    else
    {
        if(query.first())
        {
            qCDebug(databaseManager) << "\n\t\t\t[DatabaseManager] Found photo";
            //qDebug() << "selectPhoto: photo found" << query.record();
            return true;
        }
        else
        {
            qCDebug(databaseManager) << "\n\t\t\t[DatabaseManager] Error finding photo: no such photo found";
            //qDebug() << "selectPhoto: no such photo found";
        }
    }

    return false;
}

bool DatabaseManager::deletePhoto(const PhotoInformation &info, DatabaseManager::SearchCategories category)
{
    QSqlQuery query;

    switch(category)
    {
    case FileName:
        query.prepare("DELETE FROM photos WHERE fileName = (:fileName)");
        query.bindValue(":fileName", info.fileName);
        break;
    case Width:
        query.prepare("DELETE FROM photos WHERE width = (:width)");
        query.bindValue(":width", info.width);
        break;
    case Height:
        query.prepare("DELETE FROM photos WHERE height = (:height)");
        query.bindValue(":height", info.height);
        break;
    case Size:
        query.prepare("DELETE FROM photos WHERE size = (:size)");
        query.bindValue(":size", info.sizeInBytes);
        break;
    default:
        query.prepare("DELETE FROM photos WHERE fileName = (:fileName)");
        query.bindValue(":fileName", info.fileName);
        break;
    }

    if(query.exec())
    {
        qCDebug(databaseManager) << "\n\t\t\t[DatabaseManager] Photo successfully removed from database";
        //qDebug() << "deletePhoto: photo removed successfully from database";
        return true;
    }
    else
    {
        qCDebug(databaseManager) << "\n\t\t\t[DatabaseManager] Error deleting photo: " << query.lastError();
        //qDebug() << "deletePhoto: error " << query.lastError();
        return false;
    }
}

bool DatabaseManager::dropTable(const QString &tableName)
{
    QSqlQuery query;
    Q_UNUSED(tableName);
    query.prepare("DROP TABLE photos");

    if(query.exec())
    {
        qCDebug(databaseManager) << "\n\t\t\t[DatabaseManager] Table successfully dropped";
        //qDebug() << "dropTable: successfully dropped table";
        return true;
    }
    else
    {
        qCDebug(databaseManager) << "\n\t\t\t[DatabaseManager] Error dropping table: " << query.lastError();
        //qDebug() << "dropTable: error " << query.lastError();
        return false;
    }
}

QList<PhotoInformation> DatabaseManager::getDbContent(const QString &tableName)
{
    QList<PhotoInformation> result;
    QSqlQuery query;
    Q_UNUSED(tableName);
    query.prepare("SELECT * FROM photos");
    /*
    query.prepare("SELECT * FROM (:tableName)");
    query.bindValue(":tableName", tableName);*/

    if(query.exec())
    {
        qCDebug(databaseManager) << "\n\t\t\t[DatabaseManager] Successfully got database content";
        //qDebug() << "getDbContent: success";
        while(query.next())
        {
            result.append({query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(),
                           query.value(5).toUInt(), query.value(6).toUInt(), query.value(7).toULongLong()});
        }
    }
    else
    {
        qCDebug(databaseManager) << "\n\t\t\t[DatabaseManager] Failed to get database content: " << query.lastError();
        //qDebug() << "getDbContent: failed because of error " << query.lastError();
    }

    return result;
}

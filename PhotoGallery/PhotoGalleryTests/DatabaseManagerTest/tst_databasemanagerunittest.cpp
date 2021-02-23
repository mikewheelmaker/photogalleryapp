#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "databasemanager.h"

class DatabaseManagerUnitTest : public QObject
{
    Q_OBJECT

public:
    DatabaseManagerUnitTest();
    ~DatabaseManagerUnitTest();

private slots:
    void init();
    void cleanup();
    void test_createTable();
    void test_insertPhoto();
    void test_selectPhoto();
    void test_deletePhoto();
    void test_dropTable();
    void test_getDbContent();

private:
    DatabaseManager *mut = nullptr;
    PhotoInformation testInfo = {};
};

DatabaseManagerUnitTest::DatabaseManagerUnitTest()
{

}

DatabaseManagerUnitTest::~DatabaseManagerUnitTest()
{

}

void DatabaseManagerUnitTest::init()
{
    mut = new DatabaseManager("test.db");
    testInfo = {"fileURL", "filePath", "thumbnailURL", "fileName", 10, 20, 100};
}

void DatabaseManagerUnitTest::cleanup()
{
    if(mut != nullptr)
    {
        mut->dropTable("");
        delete mut;
    }
    testInfo = {};
}

void DatabaseManagerUnitTest::test_createTable()
{
    bool result = mut->createTable();
    QCOMPARE(result, true);
    result = mut->createTable();
    QCOMPARE(result, true);
    result = mut->dropTable("");
    QCOMPARE(result, true);
}

void DatabaseManagerUnitTest::test_insertPhoto()
{
    bool result = mut->insertPhoto(testInfo);
    QCOMPARE(result, false);
    mut->createTable();
    result = mut->insertPhoto(testInfo);
    QCOMPARE(result, true);
    result = mut->insertPhoto(testInfo);
    QCOMPARE(result, false);
}

void DatabaseManagerUnitTest::test_selectPhoto()
{
    bool result = mut->selectPhoto(testInfo, DatabaseManager::FileName);
    QCOMPARE(result, false);
    mut->createTable();
    mut->insertPhoto(testInfo);
    result = mut->selectPhoto(testInfo, DatabaseManager::FileName);
    QCOMPARE(result, true);
    mut->deletePhoto(testInfo, DatabaseManager::FileName);
    result = mut->selectPhoto(testInfo, DatabaseManager::FileName);
    QCOMPARE(result, false);
}

void DatabaseManagerUnitTest::test_deletePhoto()
{
    bool result = mut->deletePhoto(testInfo, DatabaseManager::FileName);
    QCOMPARE(result, false);
    mut->createTable();
    /*result = mut->deletePhoto(testInfo, DatabaseManager::FileName);
    QCOMPARE(result, false);*/
    mut->insertPhoto(testInfo);
    result = mut->deletePhoto(testInfo, DatabaseManager::FileName);
    QCOMPARE(result, true);
    /*result = mut->deletePhoto(testInfo, DatabaseManager::FileName);
    QCOMPARE(result, false);*/
}

void DatabaseManagerUnitTest::test_dropTable()
{
    bool result = mut->dropTable("");
    QCOMPARE(result, false);
    mut->createTable();
    result = mut->dropTable("");
    QCOMPARE(result, true);
    result = mut->dropTable("");
    QCOMPARE(result, false);
}

void DatabaseManagerUnitTest::test_getDbContent()
{
    QVector<PhotoInformation> testListInfo;
    testListInfo.append({"fileURL1", "filePath1", "thumbnailURL1", "fileName1", 11, 21, 101});
    testListInfo.append({"fileURL2", "filePath2", "thumbnailURL2", "fileName2", 12, 22, 102});
    testListInfo.append({"fileURL3", "filePath3", "thumbnailURL3", "fileName3", 13, 23, 103});
    testListInfo.append({"fileURL4", "filePath4", "thumbnailURL4", "fileName4", 14, 24, 104});
    testListInfo.append({"fileURL5", "filePath5", "thumbnailURL5", "fileName5", 15, 25, 105});

    QList<PhotoInformation> result = mut->getDbContent("");
    QCOMPARE(result.size(), 0);
    mut->createTable();
    mut->insertPhoto(testListInfo.at(0));
    result = mut->getDbContent("");
    QCOMPARE(result.size(), 1);
    mut->insertPhoto(testListInfo.at(1));
    mut->insertPhoto(testListInfo.at(2));
    mut->insertPhoto(testListInfo.at(3));
    mut->insertPhoto(testListInfo.at(4));
    result = mut->getDbContent("");
    QCOMPARE(result.size(), 5);
    mut->deletePhoto(testListInfo.at(0), DatabaseManager::FileName);
    result = mut->getDbContent("");
    QCOMPARE(result.size(), 4);
    mut->dropTable("");
    result = mut->getDbContent("");
    QCOMPARE(result.size(), 0);
}

QTEST_MAIN(DatabaseManagerUnitTest)

#include "debug/tst_databasemanagerunittest.moc"

#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "galleryproxymodel.h"

class GalleryProxyModelUnitTest : public QObject
{
    Q_OBJECT

public:
    GalleryProxyModelUnitTest();
    ~GalleryProxyModelUnitTest();

private slots:
    void init();
    void cleanup();
    void test_getFilter();

private:
    GalleryProxyModel *mut = nullptr;
};

GalleryProxyModelUnitTest::GalleryProxyModelUnitTest()
{

}

GalleryProxyModelUnitTest::~GalleryProxyModelUnitTest()
{

}

void GalleryProxyModelUnitTest::init()
{
    mut = new GalleryProxyModel();
}

void GalleryProxyModelUnitTest::cleanup()
{
    if(mut != nullptr)
        delete mut;
}

void GalleryProxyModelUnitTest::test_getFilter()
{
    mut->setFilter(1);
    QCOMPARE(mut->getFilter(), Qt::UserRole + 5);
    mut->setFilter(2);
    QCOMPARE(mut->getFilter(), Qt::UserRole + 6);
    mut->setFilter(3);
    QCOMPARE(mut->getFilter(), Qt::UserRole + 7);
    mut->setFilter(4);
    QCOMPARE(mut->getFilter(), Qt::UserRole + 4);
    mut->setFilter(5);
    QCOMPARE(mut->getFilter(), Qt::UserRole + 4);
    mut->setFilter(5555);
    QCOMPARE(mut->getFilter(), Qt::UserRole + 4);
    mut->setFilter(-1);
    QCOMPARE(mut->getFilter(), Qt::UserRole + 4);
}

QTEST_MAIN(GalleryProxyModelUnitTest)

#include "debug/tst_galleryproxymodelunittest.moc"

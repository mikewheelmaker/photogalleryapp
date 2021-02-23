#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "gallerymodel.h"

class GalleryModelUnitTest : public QObject
{
    Q_OBJECT

public:
    GalleryModelUnitTest();
    ~GalleryModelUnitTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

GalleryModelUnitTest::GalleryModelUnitTest()
{

}

GalleryModelUnitTest::~GalleryModelUnitTest()
{

}

void GalleryModelUnitTest::initTestCase()
{

}

void GalleryModelUnitTest::cleanupTestCase()
{

}

void GalleryModelUnitTest::test_case1()
{

}

QTEST_MAIN(GalleryModelUnitTest)

#include "debug/tst_gallerymodelunittest.moc"

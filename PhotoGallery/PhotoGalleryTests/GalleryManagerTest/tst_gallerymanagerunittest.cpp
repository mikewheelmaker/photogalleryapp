#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "gallerymanager.h"

class GalleryManagerUnitTest : public QObject
{
    Q_OBJECT

public:
    GalleryManagerUnitTest();
    ~GalleryManagerUnitTest();

private slots:
    void init();
    void cleanup();
    void test_();

private:
    GalleryManager *mut = nullptr;
};

GalleryManagerUnitTest::GalleryManagerUnitTest()
{

}

GalleryManagerUnitTest::~GalleryManagerUnitTest()
{

}

void GalleryManagerUnitTest::init()
{

}

void GalleryManagerUnitTest::cleanup()
{

}

void GalleryManagerUnitTest::test_()
{

}

QTEST_MAIN(GalleryManagerUnitTest)

#include "debug/tst_gallerymanagerunittest.moc"

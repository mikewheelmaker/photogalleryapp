#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "networkhandler.h"

Q_DECLARE_METATYPE(RequestStates)

class NetworkHandlerUnitTest : public QObject
{
    Q_OBJECT

public:
    NetworkHandlerUnitTest();
    ~NetworkHandlerUnitTest();

private slots:
    void init();
    void cleanup();
    void test_getData();
    void test_toJson();

private:
    NetworkHandler *mut = nullptr;
};

NetworkHandlerUnitTest::NetworkHandlerUnitTest()
{

}

NetworkHandlerUnitTest::~NetworkHandlerUnitTest()
{

}

void NetworkHandlerUnitTest::init()
{
    mut = new NetworkHandler();
}

void NetworkHandlerUnitTest::cleanup()
{
    if(mut != nullptr)
        delete mut;
}

void NetworkHandlerUnitTest::test_getData()
{
    qRegisterMetaType<RequestStates>();
    QSignalSpy spy(mut, &NetworkHandler::requestFinished);
    mut->get();

    QVERIFY(spy.wait(1000));
    QCOMPARE(mut->getData().size(), 5000);
}

void NetworkHandlerUnitTest::test_toJson()
{
    QSignalSpy spy(mut, &NetworkHandler::requestFinished);
    mut->get();

    QVERIFY(spy.wait(1000));
    QJsonArray result = mut->toJson(mut->getData());
    QCOMPARE(result.size(), 5000);
}

QTEST_MAIN(NetworkHandlerUnitTest)

#include "debug/tst_networkhandlerunittest.moc"

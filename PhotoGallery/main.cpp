#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>

#include "gallerymanager.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    qSetMessagePattern(QString("\n%{time yyyy-MM-dd hh:mm:ss} | %{file}(%{line})-%{function}: %{message}"));

    QGuiApplication app(argc, argv);
    GalleryManager manager;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("GalleryManager", &manager);

    engine.load(url);

    return app.exec();
}

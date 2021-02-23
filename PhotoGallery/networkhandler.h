#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QObject>
#include <QFile>
#include <QQueue>
#include <QLoggingCategory>

#include "utilities.h"

Q_DECLARE_LOGGING_CATEGORY(networkHandler)

const QString URL_GET_JSON("http://jsonplaceholder.typicode.com/photos");
const QString URL_POST_JSON("http://httpbin.org/post");

enum RequestStates {
    Inactive = 0,
    InProgress,
    Success,
    Failed
};

struct PhotoInformationJson {
    QString fullSizeUrl;
    QString thumbnailUrl;
    QString fileName;
    QJsonObject toJson() const
    {
        return {{"title", fileName}, {"url", fullSizeUrl}, {"thumbnailUrl", thumbnailUrl}};
    }
};

class NetworkHandler : public QObject
{
    Q_OBJECT
public:
    explicit NetworkHandler(QObject *parent = nullptr);
    ~NetworkHandler();

    void get();
    void post();

    void downloadPhoto(const QString &fileURL, const QString &fileName);

    QList<PhotoInformationJson> getData();
    void setData(const QList<PhotoInformationJson> &postData);

    QJsonArray toJson(const QList<PhotoInformationJson> &list);

signals:
    void requestFinished(RequestStates state);

public slots:
    void onDownloadFinished(QNetworkReply *);
    void onDownloadProgress(qint64, qint64);
    void onDownloadReadyRead();
    void onDownloadReplyFinished();

private:
    QNetworkAccessManager *m_networkAccessManager = nullptr;
    QNetworkAccessManager *m_networkAccessManagerDownload = nullptr;
    QQueue<QPair<QNetworkReply*, QFile*>> m_replyDownloads;
    QList<PhotoInformationJson> m_data;
};

#endif // NETWORKHANDLER_H

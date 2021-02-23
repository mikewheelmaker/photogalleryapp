#include <QJsonDocument>
#include <QJsonArray>
#include <QNetworkReply>
#include <QFileInfo>

#include "networkhandler.h"

Q_LOGGING_CATEGORY(networkHandler, "networkHandler.log")

NetworkHandler::NetworkHandler(QObject *parent) :
    QObject(parent),
    m_networkAccessManager(new QNetworkAccessManager(this)),
    m_networkAccessManagerDownload(new QNetworkAccessManager(this))
{
    qCDebug(networkHandler) << "\n\t\t\t[NetworkHandler] Constructor called";
}

NetworkHandler::~NetworkHandler()
{
    qCDebug(networkHandler) << "\n\t\t\t[NetworkHandler] Destructor called";
}

void NetworkHandler::get()
{
    emit requestFinished(RequestStates::InProgress);

    QUrl url{URL_GET_JSON};
    QNetworkRequest networkRequest;
    networkRequest.setUrl(url);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    connect(m_networkAccessManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply* reply)
    {
        QJsonArray result = QJsonDocument::fromJson(reply->readAll()).array();
        if (reply->error() == QNetworkReply::NoError)
        {
            m_data.clear();
            for(auto && item : result)
            {
                QJsonObject itemObject = item.toObject();
                m_data.append({itemObject.value("url").toString(),
                               itemObject.value("thumbnailUrl").toString(),
                               itemObject.value("title").toString()});
            }
            qCDebug(networkHandler) << "\n\t\t\t[NetworkHandler] Successfully got json with photos";
            //qDebug() << "successfully got json with photos";
            emit requestFinished(RequestStates::Success);
        }
        else
        {
            qCDebug(networkHandler) << "\n\t\t\t[NetworkHandler] Error on get: " << reply->error();
            //qDebug() << "error reply get" << reply->error();
            emit requestFinished(RequestStates::Failed);
        }
    });

    m_networkAccessManager->get(networkRequest);
    qCDebug(networkHandler) << "\n\t\t\t[NetworkHandler] Getting data from url: " << url;
    //qDebug() << "trying to get data from" << url;
}

void NetworkHandler::post()
{
    emit requestFinished(RequestStates::InProgress);
    QUrl url{URL_POST_JSON};
    QNetworkRequest networkRequest;

    networkRequest.setUrl(url);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    connect(m_networkAccessManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply)
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            qCDebug(networkHandler) << "\n\t\t\t[NetworkHandler] Successfully posted data";
            //qDebug() << QJsonDocument::fromJson(reply->readAll());
            emit requestFinished(RequestStates::Success);
        }
        else
        {
            qCDebug(networkHandler) << "\n\t\t\t[NetworkHandler] Error posting data: " << reply->error();
            //qDebug() << "error reply post" << reply->error();
            emit requestFinished(RequestStates::Failed);
        }
    });

    connect(m_networkAccessManager, &QNetworkAccessManager::finished, m_networkAccessManager, &QObject::deleteLater);

    m_networkAccessManager->post(networkRequest, QJsonDocument(toJson(m_data)).toJson(QJsonDocument::Compact));
    qCDebug(networkHandler) << "\n\t\t\t[NetworkHandler] Posting data to url: " << url;
    //qDebug() << "trying to post data to" << url;
}

void NetworkHandler::downloadPhoto(const QString &fileURL, const QString &fileName)
{
    emit requestFinished(RequestStates::InProgress);
    QString saveFilePath = QString("./Photos/" + fileName + ".png");

    connect(m_networkAccessManagerDownload, &QNetworkAccessManager::finished, this, &NetworkHandler::onDownloadFinished);

    QNetworkRequest request;
    request.setUrl(QUrl(fileURL));

    QNetworkReply *newReply = m_networkAccessManagerDownload->get(request);
    QFile *newFile = new QFile();
    newFile->setFileName(saveFilePath);
    newFile->open(QIODevice::WriteOnly);

    connect(newReply, &QNetworkReply::downloadProgress, this, &NetworkHandler::onDownloadProgress);
    connect(newReply, &QNetworkReply::readyRead, this, &NetworkHandler::onDownloadReadyRead);
    connect(newReply, &QNetworkReply::finished, this, &NetworkHandler::onDownloadReplyFinished);

    m_replyDownloads.enqueue(qMakePair(newReply, newFile));
}

QList<PhotoInformationJson> NetworkHandler::getData()
{
    return m_data;
}

void NetworkHandler::setData(const QList<PhotoInformationJson> &postData)
{
    m_data.clear();
    for(int i = 0; i < postData.size(); ++i)
    {
        m_data.append(postData[i]);
    }
}

QJsonArray NetworkHandler::toJson(const QList<PhotoInformationJson> &list)
{
    QJsonArray array;
    for(auto & photo : list)
        array.append(photo.toJson());
    return array;
}

void NetworkHandler::onDownloadFinished(QNetworkReply *reply)
{
    switch(reply->error())
    {
    case QNetworkReply::NoError:
        //qDebug() << "file is downloaded successfully.";
        break;
    default:
        qCDebug(networkHandler) << "\n\t\t\t[NetworkHandler] Error downloading file: " << reply->errorString().toLatin1();
        qDebug() << reply->errorString().toLatin1();
        emit requestFinished(RequestStates::Failed);
        break;
    }
}

void NetworkHandler::onDownloadProgress(qint64 bytesRead, qint64 bytesTotal)
{
    qCDebug(networkHandler) << "\n\t\t\t[NetworkHandler] DownloadProgress: " <<
                               QString::number(bytesRead).toLatin1() +" - "+ QString::number(bytesTotal).toLatin1();
    //qDebug() << QString::number(bytesRead).toLatin1() +" - "+ QString::number(bytesTotal).toLatin1();
}

void NetworkHandler::onDownloadReadyRead()
{
    QPair<QNetworkReply*,QFile*> tmp = m_replyDownloads.dequeue();
    tmp.second->write(tmp.first->readAll());
    tmp.second->close();
    tmp.second->deleteLater();
}

void NetworkHandler::onDownloadReplyFinished()
{
    emit requestFinished(RequestStates::Success);
    qCDebug(networkHandler) << "\n\t\t\t[NetworkHandler] File has been successfully downloaded";
    //qDebug() << "file is downloaded successfully.";
}

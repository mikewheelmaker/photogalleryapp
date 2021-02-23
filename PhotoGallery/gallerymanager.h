#ifndef GALLERYMANAGER_H
#define GALLERYMANAGER_H

#include "databasemanager.h"
#include "galleryproxymodel.h"
#include "networkhandler.h"

Q_DECLARE_LOGGING_CATEGORY(galleryManager)

enum ImportStatus {
    Offline = 0,
    Refresh,
    Download,
    Insert
};

class GalleryManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QAbstractListModel *galleryModel READ model CONSTANT)
    Q_PROPERTY(QAbstractItemModel *proxyModel READ proxy CONSTANT)
    Q_PROPERTY(RequestStates requestState READ getRequestState WRITE setRequestState NOTIFY requestStateChanged)
    Q_PROPERTY(int photoIndex READ getPhotoIndex WRITE setPhotoIndex NOTIFY photoIndexChanged)
    Q_PROPERTY(bool isImportStarted READ getIsImportStarted WRITE setIsImportStarted NOTIFY isImportStartedChanged)
public:
    explicit GalleryManager(QObject *parent = nullptr);
    ~GalleryManager();

    GalleryModel *model() const;
    QAbstractItemModel *proxy() const;
    RequestStates getRequestState() const;
    int getPhotoIndex() const;
    bool getIsImportStarted() const;

    Q_INVOKABLE void removePhoto(int index);
    Q_INVOKABLE void importPhotos();
    Q_INVOKABLE void exportPhotos();
    Q_INVOKABLE void clearCache();
    Q_INVOKABLE void setProxyFilter(int value);
    Q_INVOKABLE void sortProxy(int column, bool isAscendingOrder = true);
    Q_INVOKABLE void searchProxy(int role, const QString &string);

    void refresh();
    void download(const QList<PhotoInformationJson> &dataFromJson);
    void insert(const int index);
    void insertAll();

    void linkExternalSignalsToInternalSlots();

signals:
    void requestStateChanged();
    void photoIndexChanged();
    void fileOperationsCalled();
    void isImportStartedChanged();

public slots:
    void setRequestState(RequestStates value);
    void onRequestFinished(RequestStates value);
    void setPhotoIndex(int value);
    void onFileOperationsCall();
    void setIsImportStarted(bool value);

private:
    GalleryModel *m_model;
    GalleryProxyModel *m_proxy;
    DatabaseManager *m_dbManager;
    NetworkHandler *m_networkHandler;
    RequestStates m_requestState = Inactive;
    ImportStatus m_importStatus = Offline;
    int m_numberDownloads = 0;
    int m_photoIndex = -1;
    bool m_isImportStarted = false;
};

#endif // GALLERYMANAGER_H

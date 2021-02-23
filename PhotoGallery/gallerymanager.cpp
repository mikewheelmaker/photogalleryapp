#define NO_PHOTOS 25

#include <QImage>
#include <random>

#include "gallerymanager.h"

Q_LOGGING_CATEGORY(galleryManager, "galleryManager.log")

GalleryManager::GalleryManager(QObject *parent) :
    QObject(parent),
    m_model(new GalleryModel(this)),
    m_proxy(new GalleryProxyModel(this)),
    m_dbManager(new DatabaseManager("test.db")),
    m_networkHandler(new NetworkHandler(this))
{
    qCDebug(databaseManager) << "\n\t\t\t[GalleryManager] Constructor called";
    m_dbManager->createTable();
    m_proxy->setSourceModel(m_model);
    linkExternalSignalsToInternalSlots();
    connect(this, &GalleryManager::fileOperationsCalled, this, &GalleryManager::onFileOperationsCall);

    QList<PhotoInformation> dbContent = m_dbManager->getDbContent("photos");
    if(dbContent.size() != 0)
    {
        for(int i = 0; i < dbContent.size(); ++i)
        {
            m_model->addItem(dbContent[i]);
        }
    }
}

GalleryManager::~GalleryManager()
{
    delete m_dbManager;
    qCDebug(databaseManager) << "\n\t\t\t[GalleryManager] Destructor called";
}

GalleryModel* GalleryManager::model() const
{
    return m_model;
}

QAbstractItemModel *GalleryManager::proxy() const
{
    return m_proxy;
}

RequestStates GalleryManager::getRequestState() const
{
    return m_requestState;
}

int GalleryManager::getPhotoIndex() const
{
    return m_photoIndex;
}

bool GalleryManager::getIsImportStarted() const
{
    return m_isImportStarted;
}

void GalleryManager::removePhoto(int index)
{
    //QModelIndex sourceIndex = m_model->index(index, 0);
    QModelIndex proxyIndex = m_proxy->index(index, 0);
    QModelIndex sourceIndex = m_proxy->mapToSource(proxyIndex);
    m_dbManager->deletePhoto(
                {m_model->data(sourceIndex, GalleryModel::RoleFileURL).toString(),
                 m_model->data(sourceIndex, GalleryModel::RoleFilePath).toString(),
                 m_model->data(sourceIndex, GalleryModel::RoleThumbnailURL).toString(),
                 m_model->data(sourceIndex, GalleryModel::RoleFileName).toString(),
                 m_model->data(sourceIndex, GalleryModel::RoleWidth).toUInt(),
                 m_model->data(sourceIndex, GalleryModel::RoleHeight).toUInt(),
                 m_model->data(sourceIndex, GalleryModel::RoleSize).toULongLong()},
                DatabaseManager::FileName
                );
    m_model->removeItem(sourceIndex.row());
    setPhotoIndex(-1);
}

void GalleryManager::importPhotos()
{
    setIsImportStarted(true);
    delete m_networkHandler;
    m_networkHandler = new NetworkHandler(this);
    linkExternalSignalsToInternalSlots();
    refresh();
}

void GalleryManager::exportPhotos()
{

}

void GalleryManager::clearCache()
{
    if(m_requestState == Inactive)
    {
        if(m_dbManager->dropTable("photos"))
        {
            qCDebug(databaseManager) << "\n\t\t\t[GalleryManager] Successfully cleared cache";
            //qDebug() << "clearCache: table dropped successfully";
            m_model->clearList();
            m_dbManager->createTable();
        }
        else
        {
            qCDebug(databaseManager) << "\n\t\t\t[GalleryManager] Failed to drop table";
            //qDebug() << "clearCache: failed to drop table";
        }
    }
    else
    {
        qCDebug(databaseManager) << "\n\t\t\t[GalleryManager] Failed to clear cache. Database busy";
        //qDebug() << "clearCache: db busy";
    }
}

void GalleryManager::setProxyFilter(int value)
{
    m_proxy->setFilter(value);
}

void GalleryManager::sortProxy(int column, bool isAscendingOrder)
{
    m_proxy->setSortRole(Qt::UserRole + 4 + column);
    if(isAscendingOrder)
        m_proxy->sort(0, Qt::AscendingOrder);
    else
        m_proxy->sort(0, Qt::DescendingOrder);
}

void GalleryManager::searchProxy(int role, const QString &string)
{
    m_proxy->setFilter(role);
    m_proxy->setFilterFixedString(string);
}

void GalleryManager::refresh()
{
    m_importStatus = Refresh;
    m_networkHandler->get();
}

void GalleryManager::download(const QList<PhotoInformationJson> &dataFromJson)
{
    m_networkHandler->downloadPhoto(dataFromJson.at(m_numberDownloads).fullSizeUrl, dataFromJson.at(m_numberDownloads).fileName);
    ++m_numberDownloads;
}

void GalleryManager::insert(const int index)
{
    std::default_random_engine generator(time(NULL));
    std::uniform_int_distribution<int> distribution(0, 300);
    std::vector<int> randValues;
    for(int i = 0; i < NO_PHOTOS; ++i)
        randValues.push_back(distribution(generator));
    QList<PhotoInformationJson> dataFromJson = m_networkHandler->getData();
    PhotoInformationJson photo = dataFromJson[index];

    QString _fileName = "./Photos/" + photo.fileName + ".png";
    QFile fileFull(_fileName);
    int randomWidth = 300 + randValues.at(index);
    int randomHeight = 300 + randValues.at(NO_PHOTOS-1-index);
    QImage tempFull = QImage(_fileName);
    QImage imageFull = tempFull.scaled(randomWidth, randomHeight);
    if(imageFull.save(_fileName, "png"))
    {
        qCDebug(databaseManager) << "\n\t\t\t[GalleryManager] Saved modified image " << index;
        //qDebug() << "saved modified image" << index;
    }
    else
    {
        qCDebug(databaseManager) << "\n\t\t\t[GalleryManager] Unable to save image " << index;
        //qDebug() << "unable to save image" << index;
    }
    fileFull.open(QIODevice::ReadOnly);

    PhotoInformation tempInfo = {photo.fullSizeUrl, _fileName, photo.thumbnailUrl, photo.fileName + ".png",
                                 static_cast<unsigned int>(imageFull.width()),
                                 static_cast<unsigned int>(imageFull.height()),
                                 static_cast<unsigned long long>(fileFull.size())};
    if(m_dbManager->insertPhoto(tempInfo))
        m_model->addItem(tempInfo);
}

void GalleryManager::insertAll()
{
    clearCache();
    QList<PhotoInformationJson> dataFromJson = m_networkHandler->getData();
    int nrPoze = 0;
    for(auto & photo : dataFromJson)
    {
        QString _fileName = "./Photos/" + photo.fileName + ".png";
        QFile fileFull(_fileName);
        fileFull.open(QIODevice::ReadOnly);
        QImage imageFull = QImage(_fileName);
        PhotoInformation tempInfo = {photo.fullSizeUrl, fileFull.fileName(), photo.thumbnailUrl, photo.fileName + ".png",
                                     static_cast<unsigned int>(imageFull.width()),
                                     static_cast<unsigned int>(imageFull.height()),
                                     static_cast<unsigned long long>(fileFull.size())};
        m_dbManager->insertPhoto(tempInfo);
        m_model->addItem(tempInfo);
        ++nrPoze;
        if(nrPoze == m_numberDownloads)
        {
            m_numberDownloads = 0;
            return;
        }
    }
}

void GalleryManager::linkExternalSignalsToInternalSlots()
{
    connect(m_networkHandler, &NetworkHandler::requestFinished, this, &GalleryManager::onRequestFinished);
}

void GalleryManager::setRequestState(RequestStates value)
{
    if(m_requestState != value)
    {
        m_requestState = value;
        emit requestStateChanged();
    }
}

void GalleryManager::onRequestFinished(RequestStates value)
{
    setRequestState(value);
    switch(value)
    {
    case Inactive:
        qCDebug(databaseManager) << "\n\t\t\t[GalleryManager] Request state changed to INACTIVE";
        //qDebug() << "Request has become inactive";
        break;
    case InProgress:
        qCDebug(databaseManager) << "\n\t\t\t[GalleryManager] Request state changed to INPROGRESS";
        //qDebug() << "Request is in progress";
        break;
    case Success:
        qCDebug(databaseManager) << "\n\t\t\t[GalleryManager] Request state changed to SUCCESS";
        //qDebug() << "Request has finished successfully";
        m_requestState = Inactive;
        emit fileOperationsCalled();
        emit
        break;
    case Failed:
        qCDebug(databaseManager) << "\n\t\t\t[GalleryManager] Request state changed to FAILED";
        //qDebug() << "Request has finished in failure";
        m_requestState = Inactive;
        break;
    default:
        qCDebug(databaseManager) << "\n\t\t\t[GalleryManager] Request state switch error: INVALID SWITCH CASE";
        //qDebug() << "Request should not have default value!!!";
        break;
    }
}

void GalleryManager::setPhotoIndex(int value)
{
    if(m_photoIndex != value)
    {
        m_photoIndex = value;
        emit photoIndexChanged();
    }
}

void GalleryManager::onFileOperationsCall()
{
    if(m_importStatus == Refresh)
    {
        m_importStatus = Download;
        clearCache();
        m_numberDownloads = 0;
        download(m_networkHandler->getData());
    }
    else if(m_importStatus == Download && m_numberDownloads < NO_PHOTOS)
    {
        insert(m_numberDownloads-1);
        download(m_networkHandler->getData());
    }
    else if(m_importStatus == Download && m_numberDownloads == NO_PHOTOS)
    {
        m_importStatus = Insert;
        insert(m_numberDownloads-1);
        setIsImportStarted(false);
    }
}

void GalleryManager::setIsImportStarted(bool value)
{
    if(m_isImportStarted != value)
    {
        m_isImportStarted = value;
        emit isImportStartedChanged();
    }
}

#include "gallerymodel.h"

Q_LOGGING_CATEGORY(galleryModel, "galleryModel.log")

GalleryModel::GalleryModel(QObject* parent) :
    QAbstractListModel {parent}
{
    qCDebug(galleryModel, "\n\t\t\t[GalleryModel] Constructor called");
}

void GalleryModel::addItem(const PhotoInformation &itemInfo)
{
    beginResetModel();
    m_photoInformations.append(itemInfo);
    endResetModel();
    qCDebug(galleryModel, "\n\t\t\t[GalleryModel] Added item to model");
}

void GalleryModel::removeItem(int index)
{
    beginResetModel();
    m_photoInformations.removeAt(index);
    endResetModel();
    qCDebug(galleryModel, "\n\t\t\t[GalleryModel] Removed item from model");
}

void GalleryModel::clearList()
{
    beginResetModel();
    m_photoInformations.clear();
    endResetModel();
    qCDebug(galleryModel, "\n\t\t\t[GalleryModel] Removed all items from model");
}

int GalleryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_photoInformations.size();
}

QVariant GalleryModel::data(const QModelIndex &index, int role) const
{
    if(m_photoInformations.size() < index.row() && index.row() <= 0)
    {
        qCDebug(galleryModel, "\n\t\t\t[GalleryModel] Invalid index or no data to get");
        return QVariant();
    }

    switch(role)
    {
    case RoleFileURL:
        return m_photoInformations[index.row()].fileURL;
        break;
    case RoleFilePath:
        return m_photoInformations[index.row()].filePath;
        break;
    case RoleFileName:
        return m_photoInformations[index.row()].fileName;
        break;
    case RoleThumbnailURL:
        return m_photoInformations[index.row()].fileThumbnailURL;
        break;
    case RoleWidth:
        return m_photoInformations[index.row()].width;
        break;
    case RoleHeight:
        return m_photoInformations[index.row()].height;
        break;
    case RoleSize:
        return m_photoInformations[index.row()].sizeInBytes;
        break;
    /*case RoleIndex:
        return m_photoInformations[index.row()].index;
        break;*/
    default:
        qCDebug(galleryModel, "\n\t\t\t[GalleryModel] Invalid case");
        return QVariant();
        break;
    }
}

QHash<int, QByteArray> GalleryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(RoleFileURL, "fileURL");
    roles.insert(RoleFilePath, "filePath");
    roles.insert(RoleThumbnailURL, "thumbnailURL");
    roles.insert(RoleFileName, "fileName");
    roles.insert(RoleWidth, "_width");
    roles.insert(RoleHeight, "_height");
    roles.insert(RoleSize, "sizeInBytes");
    /*roles.insert(RoleIndex, "_index");*/
    //qCDebug(galleryModel, "[GalleryModel] Exposed roles from model to QML");
    return roles;
}

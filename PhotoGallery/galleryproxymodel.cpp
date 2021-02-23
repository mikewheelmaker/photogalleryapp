#include "galleryproxymodel.h"

Q_LOGGING_CATEGORY(proxyModel, "proxyModel.log")

GalleryProxyModel::GalleryProxyModel(QObject *parent) :
    QSortFilterProxyModel {parent}
{
    qCDebug(proxyModel, "\n\t\t\t[GalleryProxyModel] Constructor called");
}

GalleryProxyModel::GalleryProxyModel(GalleryModel *model)
{
    Q_UNUSED(model);
}

GalleryProxyModel::~GalleryProxyModel()
{
    qCDebug(proxyModel, "\n\t\t\t[GalleryProxyModel] Destructor called");
}

int GalleryProxyModel::getFilter() const
{
    return static_cast<int>(m_currentFilter);
}

void GalleryProxyModel::setFilter(int value)
{
    auto filterType = GalleryModel::RoleFileName;
    switch(value)
    {
    case 1:
        filterType = GalleryModel::RoleWidth;
        break;
    case 2:
        filterType = GalleryModel::RoleHeight;
        break;
    case 3:
        filterType = GalleryModel::RoleSize;
        break;
    default:
        filterType = GalleryModel::RoleFileName;
    }

    if(m_currentFilter != filterType)
    {
        m_currentFilter = filterType;
        qCDebug(proxyModel, "\n\t\t\t[GalleryProxyModel] Filter Role has been set to %d", m_currentFilter);
        setFilterRole(m_currentFilter);
        emit filterChanged();
    }
}

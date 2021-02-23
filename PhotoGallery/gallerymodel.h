#ifndef GALLERYMODEL_H
#define GALLERYMODEL_H

#include <QAbstractListModel>
#include <QLoggingCategory>

#include "utilities.h"

Q_DECLARE_LOGGING_CATEGORY(galleryModel)

class GalleryModel : public QAbstractListModel
{
public:
    GalleryModel(QObject* parent = nullptr);

    enum Roles {
        RoleFileURL = Qt::UserRole + 1,
        RoleFilePath,
        RoleThumbnailURL,
        RoleFileName,
        RoleWidth,
        RoleHeight,
        RoleSize/*,
        RoleIndex*/
    };

    void addItem(const PhotoInformation &itemInfo);
    void removeItem(int index);
    void clearList();

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<PhotoInformation> m_photoInformations;
};

#endif // GALLERYMODEL_H

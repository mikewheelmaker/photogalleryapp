#ifndef GALLERYPROXYMODEL_H
#define GALLERYPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QObject>

#include "gallerymodel.h"

Q_DECLARE_LOGGING_CATEGORY(proxyModel)

class GalleryProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(int filter READ getFilter WRITE setFilter NOTIFY filterChanged)
public:
    explicit GalleryProxyModel(QObject *parent = nullptr);
    GalleryProxyModel(GalleryModel *model);
    ~GalleryProxyModel();

    int getFilter() const;

signals:
    void filterChanged();

public slots:
    void setFilter(int value);

private:
    GalleryModel::Roles m_currentFilter;
};

#endif // GALLERYPROXYMODEL_H

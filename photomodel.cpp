#include "photomodel.h"
#include <QSqlQueryModel>
#include<QPixmap>
#include <QSqlRecord>

QVariant PhotoModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DecorationRole && index.column() == photoColumnIndex) {
        QPixmap photo;
        photo.loadFromData(record(index.row()).value("photo").toByteArray());
        return photo;
    }

    return QSqlQueryModel::data(index, role);
}

void PhotoModel::setPhotoColumnIndex(int index) {
    photoColumnIndex = index;
}

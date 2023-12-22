#ifndef PHOTOMODEL_H
#define PHOTOMODEL_H
#include <QSqlQueryModel>

class PhotoModel : public QSqlQueryModel
{   int photoColumnIndex = 0;
public:
//    PhotoModel();
//    int photoColumnIndex = 0;
public:QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void setPhotoColumnIndex(int index);
};

#endif // PHOTOMODEL_H

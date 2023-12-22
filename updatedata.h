#ifndef UPDATEDATA_H
#define UPDATEDATA_H

#include <QDialog>
#include "startwindow.h"
#include "sqlmanager.h"
#include "Player.h"
class StartWindow;
namespace Ui {
class UpdateData;
}

class UpdateData : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateData(QWidget *parent = nullptr);
    ~UpdateData();

private slots:
    void on_updatePB_clicked();

private:
    Ui::UpdateData *ui;
    StartWindow* strw;
    SQLManager* sqlM;
};

#endif // UPDATEDATA_H

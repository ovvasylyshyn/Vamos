#ifndef RENEWCONTRACT_H
#define RENEWCONTRACT_H

#include <QDialog>
#include "startwindow.h"
#include "sqlmanager.h"
#include "Player.h"
#include <QMessageBox>

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
    void on_confirmUpdatePB_clicked();

private:
    Ui::UpdateData *ui;
    StartWindow* strw;
    SQLManager* sqlM;
};

#endif // RENEWCONTRACT_H

#ifndef RENEWCOACHCONTRACT_H
#define RENEWCOACHCONTRACT_H

#include <QMainWindow>
#include "Coach.h"
#include "QMessageBox"
#include "sqlmanager.h"
class SQLManager;

namespace Ui {
class RenewCoachContract;
}

class RenewCoachContract : public QMainWindow
{
    Q_OBJECT

public:
    explicit RenewCoachContract(QWidget *parent = nullptr);
    ~RenewCoachContract();

private slots:
    void on_confirmUpdatePB_clicked();

private:
    Ui::RenewCoachContract *ui;
    SQLManager* sqlM;
};

#endif // RENEWCOACHCONTRACT_H

#ifndef UPDATEALLCOACH_H
#define UPDATEALLCOACH_H

#include <QMainWindow>
#include "Coach.h"
#include "sqlmanager.h"
#include <QMessageBox>

namespace Ui {
class UpdateAllCoach;
}

class UpdateAllCoach : public QMainWindow
{
    Q_OBJECT

public:
    explicit UpdateAllCoach(QWidget *parent = nullptr);
    ~UpdateAllCoach();

private slots:
    void on_updateCoachrPB_clicked();

private:
    Ui::UpdateAllCoach *ui;
    SQLManager* sqlM;
};

#endif // UPDATEALLCOACH_H

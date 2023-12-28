#ifndef DELETECOACHFROMTABLE_H
#define DELETECOACHFROMTABLE_H

#include <QDialog>
#include "startwindow.h"
#include "sqlmanager.h"
namespace Ui {
class DeleteCoachFromTable;
}

class DeleteCoachFromTable : public QDialog
{
    Q_OBJECT

public:
        explicit DeleteCoachFromTable(StartWindow *startWindow, SQLManager *sqlManager, QWidget *parent=nullptr);
    ~DeleteCoachFromTable();

    private slots:
        void on_deleteCoachPB_clicked();

    private:
    Ui::DeleteCoachFromTable *ui;
    SQLManager* sqlManager;
    StartWindow * startWindow;
};

#endif // DELETECOACHFROMTABLE_H

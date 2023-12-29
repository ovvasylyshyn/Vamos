#include "deletecoachfromtable.h"
#include "ui_deletecoachfromtable.h"

DeleteCoachFromTable::DeleteCoachFromTable(StartWindow *startWindow, SQLManager *sqlManager, QWidget *parent) :
    QDialog(parent), ui(new Ui::DeleteCoachFromTable), startWindow(startWindow), sqlManager(sqlManager) {

    ui->setupUi(this);
    sqlManager = new SQLManager;
    sqlManager->connectToDataBase();
}

DeleteCoachFromTable::~DeleteCoachFromTable()
{
    delete ui;
}

void DeleteCoachFromTable::on_deleteCoachPB_clicked()
{
    int coachIdToDelete = ui->deleteIDLE->text().toInt();

    bool success = sqlManager->deleteCoachFromTable(coachIdToDelete);
    if (success) {
        QMessageBox::information(this, "Coach deleted", "Coach deleted!");
        hide();
    } else {
        QMessageBox::warning(this, "Error", "Something went wrong, try again");
        hide();
    }
}


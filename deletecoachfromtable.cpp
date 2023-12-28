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
{Coach deleted;
    int coachIdToDelete = ui->deleteIDLE->text().toInt();
    QString coachName = QString::fromStdString(ui->nameLE->text().toStdString());
    QString coachSurName= QString::fromStdString(ui->surnameLE->text().toStdString());
    bool success = sqlManager->deleteCoachFromTable(coachIdToDelete,coachName,coachSurName);
    if (success) {
        sqlManager->inserIntoTableDeleteCoach(deleted);
        QMessageBox::information(this, "Coach deleted", "Coach deleted!");
        hide();
    } else {
        QMessageBox::warning(this, "Error", "Something went wrong, try again");
        hide();
    }
}


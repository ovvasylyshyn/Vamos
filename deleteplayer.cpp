#include "deleteplayer.h"
#include "ui_deleteplayer.h"

    DeletePlayer::DeletePlayer(StartWindow *startWindow, SQLManager *sqlManager, QWidget *parent)
    : QDialog(parent), ui(new Ui::DeletePlayer), startWindow(startWindow), sqlManager(sqlManager)
{
    ui->setupUi(this);
    sqlManager = new SQLManager;
    sqlManager->connectToDataBase();
}

DeletePlayer::~DeletePlayer()
{
    delete ui;
}

void DeletePlayer::on_deletePlayerPB_clicked()
{
    Player deleted;
    int playerIdToDelete = ui->deleteIDLE->text().toInt();
    QString playerName = QString::fromStdString(ui->nameLE->text().toStdString());
    QString playerSurName= QString::fromStdString(ui->surnameLE->text().toStdString());
    bool success = sqlManager->deletePlayerFromTable(playerIdToDelete,playerName,playerSurName);
    if (success) {
        QMessageBox::information(this, "Player deleted", "Player delete!");
         sqlManager->inserIntoTableDeletedPlayer(deleted);
        hide();
    } else {
        QMessageBox::warning(this, "Error", "Something went wrong, try again");
        hide();
    }
}


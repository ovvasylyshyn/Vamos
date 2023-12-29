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
    int playerIdToDelete = ui->deleteIDLE->text().toInt();

    bool success = sqlManager->deletePlayerFromTable(playerIdToDelete);
    if (success) {
        QMessageBox::information(this, "Player deleted", "Player delete!");
        hide();
    } else {
        QMessageBox::warning(this, "Error", "Something went wrong, try again");
        hide();
    }
}


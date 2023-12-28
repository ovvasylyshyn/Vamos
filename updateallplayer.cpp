#include "updateallplayer.h"
#include "ui_updateallplayer.h"

UpdateAllPlayer::UpdateAllPlayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateAllPlayer)
{
    ui->setupUi(this);
}

UpdateAllPlayer::~UpdateAllPlayer()
{
    delete ui;
}

void UpdateAllPlayer::on_updatePlayerPB_clicked()
{
    Player player;
    player.setId(ui->idLE->text().toInt());
    player.setName(ui->nameLE->text().toStdString());
    player.setSurName(ui->surnameLE->text().toStdString());
     player.setAge(ui->ageSB->value());
    player.setContractEndDate(ui->contractEndDE->date());
    player.setContractExpiry(ui->clubContractDE->date());
    if (ui->footCB->currentIndex() == 0)
        player.setPreferredFoot(Foot::LEFT);
    else if (ui->footCB->currentIndex() == 1)
        player.setPreferredFoot(Foot::RIGHT);
    else
        player.setPreferredFoot(Foot::BOTH);
        player.setLeague(ui->leagueLE->text().toStdString());
        player.setClub(ui->clubLE->text().toStdString());
            player.setNumber(ui->numberSB->value());
            player.setPrice(ui->priceLE->text().toInt());
    if (sqlM->updatePlayer(player)) {
        QString message = QString("Data for %1 %2 renewed!")
                              .arg(ui->nameLE->text())
                              .arg(ui->surnameLE->text());

        QMessageBox::about(this, "Renew Contract", message);
        qDebug() << "Player updated successfully";
        hide();
    } else {
        qDebug() << "Failed to update player";
        QMessageBox::critical(this, "Renew Contract", "Contract isn't renewed!");

    }
}


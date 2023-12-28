#include "RenewContract.h"
//#include "ui_updatedata.h"
#include "ui_RenewContract.h"
UpdateData::UpdateData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateData)
{
    ui->setupUi(this);
}

UpdateData::~UpdateData()
{
    delete ui;
}

void UpdateData::on_confirmUpdatePB_clicked()
{
    Player player;
    player.setId(ui->idLE->text().toInt());
    player.setName(ui->nameLE->text().toStdString());
    player.setSurName(ui->surnameLE->text().toStdString());
    player.setContractEndDate(ui->contractEndDE->date());

    if (sqlM->updatePlayer(player)) {
        QString message = QString("Contract for %1 %2 renewed!\nNew contract end date: %3")
                              .arg(ui->nameLE->text())
                              .arg(ui->surnameLE->text())
                              .arg(ui->contractEndDE->date().toString("yyyy-MM-dd"));

        QMessageBox::about(this, "Renew Contract", message);
        qDebug() << "Player updated successfully";
        hide();
    } else {
        qDebug() << "Failed to update player";
        QMessageBox::critical(this, "Renew Contract", "Contract isn't renewed!");
}

}


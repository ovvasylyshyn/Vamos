#include "renewcoachcontract.h"
#include "ui_renewcoachcontract.h"

RenewCoachContract::RenewCoachContract(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RenewCoachContract)
{
    ui->setupUi(this);
}

RenewCoachContract::~RenewCoachContract()
{
    delete ui;
}

void RenewCoachContract::on_confirmUpdatePB_clicked()
{
    Coach coach;
    coach.setId(ui->idLE->text().toInt());
    coach.setName(ui->nameLE->text().toStdString());
    coach.setSurName(ui->surnameLE->text().toStdString());
    coach.setContractEndDate(ui->contractEndDE->date());

    if (sqlM->updateCoach(coach)) {
        QString message = QString("Contract for %1 %2 renewed!\nNew contract end date: %3")
                              .arg(ui->nameLE->text())
                              .arg(ui->surnameLE->text())
                              .arg(ui->contractEndDE->date().toString("yyyy-MM-dd"));

        QMessageBox::about(this, "Renew Contract", message);
        qDebug() << "Coach updated successfully";
        hide();
    } else {
        qDebug() << "Failed to update coach";
        QMessageBox::critical(this, "Renew Contract", "Contract isn't renewed!");

    }
}


#include "updateallcoach.h"
#include "ui_updateallcoach.h"

UpdateAllCoach::UpdateAllCoach(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UpdateAllCoach)
{
    ui->setupUi(this);
}

UpdateAllCoach::~UpdateAllCoach()
{
    delete ui;
}

void UpdateAllCoach::on_updateCoachrPB_clicked()
{
    Coach newCoach;
    newCoach.setId(ui->idLE_5->text().toInt());
    newCoach.setName(ui->nameLE_5->text().toStdString());
    newCoach.setSurName(ui->surnameLE_5->text().toStdString());
    newCoach.setLastName(ui->lastNameLE_5->text().toStdString());
    newCoach.setAge(ui->ageSB_5->value());
    newCoach.setContractEndDate(ui->contractEndDE_5->date());
    newCoach.setCoachContractExpiry(ui->coachExpitryDE_3->date());
    newCoach.setClub(ui->clubLE_5->text().toStdString());
    newCoach.setExpirience(ui->experienceSB_3->value());
    if (ui->typeCB_3->currentIndex() == 1)
        newCoach.setType("Head_coach");
    else if (ui->typeCB_3->currentIndex() == 2)
        newCoach.setType("Assistant coach");
    else if (ui->typeCB_3->currentIndex() == 3)
        newCoach.setType("Physics coach");
    else if (ui->typeCB_3->currentIndex() == 4)
        newCoach.setType("Goalkeper coach");
    if (sqlM->UpdateCoachAll(newCoach)) {
        QString message = QString("Data for %1 %2 renewed!")
                              .arg(ui->nameLE_5->text())
                              .arg(ui->surnameLE_5->text());

        QMessageBox::about(this, "Renew Contract", message);
        qDebug() << "Coach updated successfully";
        hide();
    } else {
        qDebug() << "Failed to update coach";
        QMessageBox::critical(this, "Renew Contract", "Contract isn't renewed!");
   }
}


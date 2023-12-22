#include "updatedata.h"
#include "ui_updatedata.h"

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

void UpdateData::on_updatePB_clicked()
{
//    QString id, name, surname, contractEndDate;
//    id=ui->idLE->text();
//    id=ui->nameLE->text();
//    id=ui->surnameLE->text();
//    id=ui->contractEndDE->text();
    Player player;

    // Заповнюємо об'єкт player даними, наприклад, з деякого іншого методу або користувацького введення
    player.setId(ui->idLE->text().toInt());
    player.setName(ui->nameLE->text().toStdString());
    player.setSurName(ui->surnameLE->text().toStdString());
    player.setContractEndDate(ui->contractEndDE->date());
    if (sqlM->updatePlayer(player)) {
        // Опційно: Додайте обробник успішного оновлення
        qDebug() << "Player updated successfully";
    } else {
        // Опційно: Додайте обробник помилки оновлення
        qDebug() << "Failed to update player";
    }
//    QSqlQuery qry;
//    qry.prepare("UPDATE player SET id='"+id+"',name='"+name+"',surname='"+surname+"',contractEndDate='"+contractEndDate+"' WHERE id='"+id+"'");
}

//void StartWindow::addPlayer() {
//    Player newPlayer;
//    newPlayer.setId(ui->idLE->text().toInt());
//    newPlayer.setName(ui->nameLE->text().toStdString());
//    newPlayer.setSurName(ui->surnameLE->text().toStdString());
//    newPlayer.setLastName(ui->lastNameLE->text().toStdString());
//    newPlayer.setAge(ui->ageSB->value());
//    newPlayer.setContractEndDate(ui->contractEndDE->date());
//    newPlayer.setContractExpiry(ui->clubContractDE->date());
//    if (ui->footCB->currentIndex() == 0)
//        newPlayer.setPreferredFoot(Foot::LEFT);
//    //newPlayer.setPreferredFoot("Left");
//    else if (ui->footCB->currentIndex() == 1)
//        newPlayer.setPreferredFoot(Foot::RIGHT);
//    // newPlayer.setPreferredFoot("Right");
//    else
//        newPlayer.setPreferredFoot(Foot::BOTH);
//    //newPlayer.setPreferredFoot("Both");
//    newPlayer.setLeague(ui->leagueLE->text().toStdString());
//    newPlayer.setClub(ui->clubLE->text().toStdString());
//    newPlayer.setNumber(ui->numberSB->value());
//    newPlayer.setPrice(ui->priceLE->text().toDouble());
//    loadPhoto(newPlayer);
//    bool success = sqlM->inserIntoTablePlayer(newPlayer);
//    if (success) {
//        QMessageBox::information(this, "Гравець доданий", "Гравець був успішно доданий до бази даних.");
//        int currentIndex = ui->tabWidget->currentIndex();
//        ui->tabWidget->removeTab(currentIndex);
//    } else {
//        QMessageBox::warning(this, "Помилка", "Помилка при додаванні гравця до бази даних.");
//    }
//}

//void StartWindow::loadPhoto(Player& newPlayer) {
//    QString photoFilePath = QFileDialog::getOpenFileName(nullptr, "Виберіть фотографію", QDir::homePath(), "Desktop (*.png *.jpg *.jpeg)");
//    if (!photoFilePath.isEmpty()) {
//        QPixmap photo(photoFilePath);
//        QByteArray photoData;
//        QBuffer buffer(&photoData);
//        buffer.open(QIODevice::WriteOnly);
//        photo.save(&buffer, "JPG");
//        newPlayer.setPhotoData(photoData);
//    } else {
//        qDebug() << "Вибір фотографії скасовано";
//    }
//}

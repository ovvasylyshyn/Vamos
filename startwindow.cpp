#include "startwindow.h"
#include "ui_startwindow.h"
#include "signin.h"
#include "signup.h"
#include <QMessageBox>
#include <QFileDialog>
#include<QFile>
#include <QBuffer>
#include <QSqlError>
#include <QModelIndexList>
#include<QInputDialog>

StartWindow::StartWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    signIn= new SignIn();
    signUp = new SignUp();
    sqlM = new SQLManager;
    updateD= new UpdateData;
    sqlM->connectToDataBase();
    ui->nextPB->hide();
    ui->updatePB->hide();
    ui->tabWidget->setTabText(0, "Enter window");
    ui->tabWidget->setTabText(1, "Main window");
    ui->tabWidget->setTabEnabled(1,false);
    ui->tabWidget->setTabEnabled(2,false);
    ui->tabWidget->setTabEnabled(3,false);
    ui->tabWidget->setTabEnabled(4,false);
    ui->tabWidget->setTabEnabled(5,false);
    ui->tabWidget->setTabText(2,"Add player");
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_signInPB_clicked()
{
    signIn->show();
    ui->nextPB->show();
    ui->welocomeL->setText("Thank you!");
}


void StartWindow::on_signUpPB_clicked()
{
    signUp->show();
    ui->nextPB->show();
    ui->welocomeL->setText("Thank you!");
}


void StartWindow::on_nextPB_clicked()
{
    int targetTabIndex = 1;
    ui->tabWidget->setCurrentIndex(targetTabIndex);
    ui->tabWidget->setTabEnabled(1,true);
     ui->tabWidget->setTabEnabled(2,true);
     ui->tabWidget->setTabEnabled(3,true);
     ui->tabWidget->setTabEnabled(4,true);
      ui->tabWidget->setTabEnabled(5,true);
    ui->tabWidget->setCurrentWidget(ui->mainWindow);
}

void StartWindow::on_addPlayerPB_clicked()
{
     ui->tabWidget->setCurrentWidget(ui->addPlayer);
}

void StartWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (index >= 0 && index < ui->tabWidget->count()) {
        ui->tabWidget->removeTab(index);
    }
}

void StartWindow::addPlayer() {
    Player newPlayer;
    newPlayer.setId(ui->idLE->text().toInt());
    newPlayer.setName(ui->nameLE->text().toStdString());
    newPlayer.setSurName(ui->surnameLE->text().toStdString());
    newPlayer.setLastName(ui->lastNameLE->text().toStdString());
    newPlayer.setAge(ui->ageSB->value());
    newPlayer.setContractEndDate(ui->contractEndDE->date());
    newPlayer.setContractExpiry(ui->clubContractDE->date());
    if (ui->footCB->currentIndex() == 0)
        newPlayer.setPreferredFoot(Foot::LEFT);
    else if (ui->footCB->currentIndex() == 1)
       newPlayer.setPreferredFoot(Foot::RIGHT);
    else
       newPlayer.setPreferredFoot(Foot::BOTH);
    newPlayer.setLeague(ui->leagueLE->text().toStdString());
    newPlayer.setClub(ui->clubLE->text().toStdString());
    newPlayer.setNumber(ui->numberSB->value());
    newPlayer.setPrice(ui->priceLE->text().toDouble());
    loadPhoto(newPlayer);
    bool success = sqlM->inserIntoTablePlayer(newPlayer);
    if (success) {
        QMessageBox::information(this, "Player added", "Player was added to daatabase");
       ui->tabWidget->currentIndex();
         ui->tabWidget->setCurrentWidget(ui->mainWindow);
    } else {
        QMessageBox::warning(this, "Error", "Something went wrong");
 }
}

void StartWindow::loadPhoto(Player& newPlayer) {
 QString photoFilePath = QFileDialog::getOpenFileName(nullptr, "Виберіть фотографію", QDir::homePath(), "Desktop (*.png *.jpg *.jpeg)");
  if (!photoFilePath.isEmpty()) {
 QPixmap photo(photoFilePath);
        QByteArray photoData;
        QBuffer buffer(&photoData);
        buffer.open(QIODevice::WriteOnly);
        photo.save(&buffer, "JPG");
        newPlayer.setPhotoData(photoData);
  } else {
        qDebug() << "Вибір фотографії скасовано";
  }
}

void StartWindow::on_showPlayersPB_clicked()
{
  PhotoModel* model = sqlM->getAllPlayers();
  QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
  proxyModel->setSourceModel(model);
 ui->playersTV->verticalHeader()->setDefaultSectionSize(80);
  ui->playersTV->horizontalHeader()->setDefaultSectionSize(80);
  ui->playersTV->setModel(proxyModel);
  ui->playersTV->setSortingEnabled(true);
  int targetTabIndex = 3;
  ui->tabWidget->setCurrentIndex(targetTabIndex);
  ui->idL->clear();
  ui->nameL->clear();
  ui->surnameL->clear();
  ui->lastNameL->clear();
  ui->ageL_2->clear();
  ui->contractEndL->clear();
  ui->clubContractL_2->clear();
  ui->prefferedFootL->clear();
  ui->leagueL->clear();
  ui->clubL->clear();
  ui->numberL_2->clear();
  ui->priceL->clear();
  ui->photoL->clear();
}

void StartWindow::on_addPlayerToTablePB_clicked()
{
    addPlayer();
}

void StartWindow::on_playersTV_activated(const QModelIndex &index)
{
    QString val = ui->playersTV->model()->data(index).toString();

    QSqlQuery qry = sqlM->selectPlayerByPhotoOrName(val);
    if (qry.next()) {
        ui->idL->setText(qry.value(0).toString());
        ui->nameL->setText(qry.value(1).toString());
        ui->surnameL->setText(qry.value(2).toString());
        ui->lastNameL->setText(qry.value(3).toString());
        ui->ageL_2->setText(qry.value(4).toString());
        ui->contractEndL->setText(qry.value(5).toString());
        ui->clubContractL_2->setText(qry.value(6).toString());
        ui->prefferedFootL->setText(qry.value(7).toString());
        ui->leagueL->setText(qry.value(8).toString());
        ui->clubL->setText(qry.value(9).toString());
        ui->numberL_2->setText(qry.value(10).toString());
        ui->priceL->setText(qry.value(11).toString());
        QByteArray photoData = qry.value(12).toByteArray();
        QPixmap playerPhoto;
        playerPhoto.loadFromData(photoData);
        ui->photoL->setPixmap(playerPhoto);
    } else {
        qDebug() << "no player`s data";
    }
    ui->updatePB->show();
}

void StartWindow::on_updatePB_clicked()
{
    updateD->show();
    ui->idL->clear();
    ui->nameL->clear();
    ui->surnameL->clear();
    ui->lastNameL->clear();
    ui->ageL_2->clear();
    ui->contractEndL->clear();
    ui->clubContractL_2->clear();
    ui->prefferedFootL->clear();
    ui->leagueL->clear();
    ui->clubL->clear();
    ui->numberL_2->clear();
    ui->priceL->clear();
    ui->photoL->clear();
      ui->tabWidget->setCurrentWidget(ui->mainWindow);
}

void StartWindow::on_deletePB_clicked()
{
    DeletePlayer deletePlayerWindow(this, sqlM);
    deletePlayerWindow.exec();
}

void StartWindow::on_updateAllPB_clicked()
{
    updateAll= new UpdateAllPlayer();
    updateAll->show();
    ui->idL->clear();
    ui->nameL->clear();
    ui->surnameL->clear();
    ui->lastNameL->clear();
    ui->ageL_2->clear();
    ui->contractEndL->clear();
    ui->clubContractL_2->clear();
    ui->prefferedFootL->clear();
    ui->leagueL->clear();
    ui->clubL->clear();
    ui->numberL_2->clear();
    ui->priceL->clear();
    ui->photoL->clear();
      ui->tabWidget->setCurrentWidget(ui->mainWindow);
}

void StartWindow::addCoach() {
    Coach newCoach;
    newCoach.setId(ui->idLE_2->text().toInt());
    newCoach.setName(ui->nameLE_2->text().toStdString());
    newCoach.setSurName(ui->surnameLE_2->text().toStdString());
    newCoach.setLastName(ui->lastNameLE_2->text().toStdString());
    newCoach.setAge(ui->ageSB_2->value());
    QDate currentDate = QDate::currentDate();
    newCoach.setContractEndDate(ui->contractEndDE_2->date());
    newCoach.setCoachContractExpiry(ui->coachExpitryDE->date());
    newCoach.setClub(ui->clubLE_2->text().toStdString());
    newCoach.setExpirience(ui->experienceSB->value());
    if (ui->typeCB->currentIndex() == 1)
        newCoach.setType("Head_coach");
    else if (ui->typeCB->currentIndex() == 2)
        newCoach.setType("Assistant coach");
   else if (ui->typeCB->currentIndex() == 3)
        newCoach.setType("Physics coach");
    else if (ui->typeCB->currentIndex() == 4)
        newCoach.setType("Goalkeper coach");
    ui->contractEndDE_2->setMaximumDate(currentDate);
    ui->coachExpitryDE->setMaximumDate(currentDate);

    loadPhotoToCoach(newCoach);
    bool success = sqlM->inserIntoTableCoach(newCoach);
    if (success) {
        QMessageBox::information(this, "coach aded", "Coach was added to database");
         ui->tabWidget->currentIndex();
          ui->tabWidget->setCurrentWidget(ui->mainWindow);
    } else {
        QMessageBox::warning(this, "error", "Something went wrong");
    }
}

void StartWindow::loadPhotoToCoach(Coach& newCoach) {
    QString photoFilePath = QFileDialog::getOpenFileName(nullptr, "Виберіть фотографію", QDir::homePath(), "Desktop (*.png *.jpg *.jpeg)");
    if (!photoFilePath.isEmpty()) {
        QPixmap photo(photoFilePath);
        QByteArray photoData;
        QBuffer buffer(&photoData);
        buffer.open(QIODevice::WriteOnly);
        photo.save(&buffer, "JPG");
        newCoach.setPhotoData(photoData);
    } else {
        qDebug() << "Вибір фотографії скасовано";
    }
}
void StartWindow::on_addPlayerToTablePB_2_clicked()
{
    addCoach();
}


void StartWindow::on_addCoachPB_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->addCoach);
}


void StartWindow::on_showCoachPB_clicked()
{
    PhotoModel* model = sqlM->getAllCoaches();
    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->coachTV->verticalHeader()->setDefaultSectionSize(80);
    ui->coachTV->setModel(proxyModel);
    ui->coachTV->setSortingEnabled(true);
    int targetTabIndex = 5;
    ui->tabWidget->setCurrentIndex(targetTabIndex);
}

void StartWindow::on_renewContractPB_clicked()
{
  renewCoach=new RenewCoachContract;
    renewCoach->show();
    ui->tabWidget->setCurrentWidget(ui->mainWindow);
}


void StartWindow::on_updateAllCPB_clicked()
{
    updateAllC= new UpdateAllCoach;
    updateAllC->show();
    ui->tabWidget->setCurrentWidget(ui->mainWindow);
}


void StartWindow::on_deletePlayerPB_clicked()
{

    DeleteCoachFromTable deleteCoachWindow(this,sqlM);
        deleteCoachWindow.exec();
}


void StartWindow::on_quitPB_clicked()
{
        QApplication::quit();
}


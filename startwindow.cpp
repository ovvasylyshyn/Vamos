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
    ui->mainWindow->setVisible(false);
    ui->tabWidget->setTabText(2,"Add player");
   // connect(ui->updatePB, &QPushButton::clicked, this, &Upda)
//    connect(ui->searchLE, &QLineEdit::textChanged, this, &StartWindow::onSearchTextChanged);
//    setupModel();
   // connect(ui->addPB, &QPushButton::clicked, this, &StartWindow::loadPhoto);
    //connect(ui->addPlayerToTablePB, &QPushButton::clicked, this, &StartWindow::addPlayer);
  // connect(ui->addPB, &QPushButton::clicked, this, &StartWindow::loadPhoto);
  //  connect(ui->photoPB, &QPushButton::clicked, this, &StartWindow::on_photoPB_clicked);
    //connect(ui->signInPB, SIGNAL(clicked()), this, SLOT(on_signInPB_clicked()));
  //  connect(ui->signUpPB, SIGNAL(clicked()), this, SLOT(on_signUpPB_clicked()));

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
    ui->mainWindow->setVisible(true);
    ui->tabWidget->setCurrentWidget(ui->mainWindow);
    QString userLogin = sqlM->getLoginFromDatabase();
     if (!userLogin.isEmpty()) {;
    } else {
        QMessageBox::warning(this, "Попередження", "Будь ласка, зареєструйтеся або увійдіть в систему.");
    }
}

void StartWindow::on_addPlayerPB_clicked()
{
     ui->tabWidget->setCurrentWidget(ui->addPlayer);
}

void StartWindow::on_tabWidget_tabCloseRequested(int index)
{
   // ui->tabWidget->removeTab(2);
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
    //newPlayer.setPreferredFoot("Left");
    else if (ui->footCB->currentIndex() == 1)
       newPlayer.setPreferredFoot(Foot::RIGHT);
    // newPlayer.setPreferredFoot("Right");
    else
       newPlayer.setPreferredFoot(Foot::BOTH);
      //newPlayer.setPreferredFoot("Both");
    newPlayer.setLeague(ui->leagueLE->text().toStdString());
    newPlayer.setClub(ui->clubLE->text().toStdString());
    newPlayer.setNumber(ui->numberSB->value());
    newPlayer.setPrice(ui->priceLE->text().toDouble());
    loadPhoto(newPlayer);
    bool success = sqlM->inserIntoTablePlayer(newPlayer);
    if (success) {
        QMessageBox::information(this, "Гравець доданий", "Гравець був успішно доданий до бази даних.");
        int currentIndex = ui->tabWidget->currentIndex();
        ui->tabWidget->removeTab(currentIndex);
        } else {
        QMessageBox::warning(this, "Помилка", "Помилка при додаванні гравця до бази даних.");
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
    PhotoModel* modal = sqlM->getAllPlayers();
    ui->playersTV->setModel(modal);
    ui->playersTV->verticalHeader()->setDefaultSectionSize(150);
    ui->showPlayer->show();
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






//void StartWindow::setupModel()
//{
//    model = new QSqlQueryModel(this);
//    ui->playersTV->setModel(model);
//}
//void StartWindow::onSearchTextChanged(const QString &text)
//{
//    SQLManager sqlM;
//    QSqlQuery qry = sqlM.searchPlayer(text);

//    if (qry.exec()) {
//        model->setQuery(qry);
//    } else {
//        qDebug() << "Error executingg query:" << qry.lastError().text();
//    }
//}
//void searchPlayer() {
//    Player player(ui->idL->text(), teamLineEdit->text(), jerseyNumberSpinBox->value());

//    QSqlQuery query = dbManager->searchPlayer(player);

//    if (query.next()) {
//        // Вивести дані гравця на етикетки
//        QString playerNameResult = query.value("name").toString();
//        QString playerScoreResult = query.value("score").toString();

//        nameLabel->setText("Player Name: " + playerNameResult);
//        scoreLabel->setText("Player Score: " + playerScoreResult);
//    } else {
//        // Гравець не знайдений
//        nameLabel->setText("Player not found");
//        scoreLabel->clear();
//    }
//}








void StartWindow::on_updatePB_clicked()
{
    updateD->show();
}


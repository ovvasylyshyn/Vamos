#include "signup.h"
#include "ui_signup.h"
#include <QMessageBox>
#include <QCryptographicHash>

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);
    sqlM = new SQLManager;
    sqlM->connectToDataBase();
   // connect(ui->registrPB, &QPushButton::clicked, startWindow, &StartWindow::show);

}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_registrPB_clicked()
{
    QString login= ui->loginLE->text();
    QString password = ui->passwordLE->text();
    if(!login.isEmpty()&&!password.isEmpty())
    {
    if (sqlM->userExists(login)) {
        QMessageBox::warning(this, "Duplicate User", "Користувач з таким логіном вже існує. Виберіть інший логін.");
        return;
    }
            QCryptographicHash hash(QCryptographicHash::Sha256);
            hash.addData(password.toUtf8());
            QByteArray hashedData = hash.result();
            QString hashedDataString = hashedData.toHex();

            sqlM->inserIntoTableRegistration(login,hashedDataString);
            QMessageBox::about(this, "Entrance to system", "Registration was successful");
            //sqlM->clearRegistrationTable();
    }
    else{QMessageBox::critical(this,"Fail","U have an empty string");}
    ui->loginLE->clear();
    ui->passwordLE->clear();
    this->close();
}


#include "signin.h"
#include "ui_signin.h"
#include<QMessageBox>
#include <QCryptographicHash>

SignIn::SignIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);
    sqlM = new SQLManager;
    sqlM->connectToDataBase();
}

SignIn::~SignIn()
{
    delete ui;
}

void SignIn::on_signInPB_clicked()
{
    QString login = ui->inLoginLE->text();
    QString password = ui->passwordLE->text();


    if(!login.isEmpty()&&!password.isEmpty())
    {

            QCryptographicHash hash(QCryptographicHash::Sha256);
            hash.addData(password.toUtf8());
            QByteArray hashedData = hash.result();
            QString hashedDataString = hashedData.toHex();
            bool check= sqlM->login(login,hashedDataString);
            if(check)
            {
                QMessageBox::about(this, "Entrance to system", "Login successful");
//                emit home();

            }
            else  { QMessageBox::critical(this,"Login Failed","Incorrect login or password. Please try again");}

    }
    else{QMessageBox::critical(this,"Fail","U have an empty string");
    }
    ui->inLoginLE->clear();
    ui->passwordLE->clear();
    this->close();

//    // Перевірка наявності користувача з введеним логіном і паролем в базі даних
//    if (sqlM->validateUser(login, password)) {
//        QMessageBox::about(this, "Entrance to system", "Login successful");
//        // Тут ви можете виконати додаткові дії, які необхідні після входу
//    } else {
//        QMessageBox::warning(this, "Login Failed", "Incorrect login or password. Please try again.");
//    }
}


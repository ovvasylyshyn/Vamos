#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QSqlDatabase>
#include "sqlmanager.h"

namespace Ui {
class SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

private slots:
    void on_registrPB_clicked();

private:
    Ui::SignUp *ui;
      SQLManager *sqlM;
};

#endif // SIGNUP_H

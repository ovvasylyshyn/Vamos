#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>
#include <QSqlDatabase>
#include "sqlmanager.h"

namespace Ui {
class SignIn;
}

class SignIn : public QDialog
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = nullptr);
    ~SignIn();

private slots:
    void on_signInPB_clicked();

private:
    Ui::SignIn *ui;
     SQLManager *sqlM;
};

#endif // SIGNIN_H

#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>
#include "signin.h"
#include"signup.h"
#include "sqlmanager.h"
#include"Player.h"
#include <QSqlTableModel>
#include<QTableView>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <updatedata.h>

class UpdateData;
namespace Ui {
class StartWindow;
}

class StartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();


private slots:
    void on_signInPB_clicked();

    void on_signUpPB_clicked();

    void on_nextPB_clicked();

    void on_addPlayerPB_clicked();

    void on_tabWidget_tabCloseRequested(int index);

    void on_showPlayersPB_clicked();

    void on_addPlayerToTablePB_clicked();

    void on_playersTV_activated(const QModelIndex &index);



    void on_updatePB_clicked();

private:
    Ui::StartWindow *ui;
   SignIn* signIn;
    SignUp* signUp;
   SQLManager *sqlM;
    UpdateData* updateD;
     QSqlQueryModel *model;
    void addPlayer();
   void loadPhoto(Player& newPlayer);
//    void onSearchTextChanged(const QString &text);
//   void setupModel();

};

#endif // STARTWINDOW_H

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
#include <RenewContract.h>
#include <QTabWidget>
#include "deleteplayer.h"
#include <QDate>
#include <QSortFilterProxyModel>
#include"updateallplayer.h"
#include "renewcoachcontract.h"
#include "updateallcoach.h"
#include "deletecoachfromtable.h"

class DeleteCoachFromTable;
class RenewCoachContract;
class DeletePlayer;
class SignUp;
class SignIn;
class UpdateData;
class UpdateAllPlayer;
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

    void on_deletePB_clicked();

    void on_updateAllPB_clicked();

    void on_addPlayerToTablePB_2_clicked();

    void on_addCoachPB_clicked();

    void on_showCoachPB_clicked();

    void on_renewContractPB_clicked();

    void on_updateAllCPB_clicked();

    void on_deletePlayerPB_clicked();

    void on_quitPB_clicked();

private:
    Ui::StartWindow *ui;
   SignIn* signIn;
    SignUp* signUp;
   SQLManager *sqlM;
    UpdateData* updateD;
     QSqlQueryModel *model;
    DeletePlayer* deletePlayer;
     UpdateAllPlayer* updateAll;
    RenewCoachContract * renewCoach;
     UpdateAllCoach* updateAllC;
    DeleteCoachFromTable* deleteCoach;
    void addPlayer();
   void loadPhoto(Player& newPlayer);
   void displaySearchResults(const QList<Player>& searchResults);
   void addCoach();
 void loadPhotoToCoach(Coach& newCoach);
};

#endif // STARTWINDOW_H

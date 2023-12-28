#ifndef DELETEPLAYER_H
#define DELETEPLAYER_H

#include <QDialog>
#include "sqlmanager.h"
#include <QMessageBox>
#include"startwindow.h"
#include"sqlmanager.h"

namespace Ui {
class DeletePlayer;
}

class DeletePlayer : public QDialog
{
    Q_OBJECT

public:
    explicit DeletePlayer(StartWindow *startWindow, SQLManager *sqlManager, QWidget *parent=nullptr);
    ~DeletePlayer();

private slots:
    void on_deletePlayerPB_clicked();

private:
    Ui::DeletePlayer *ui;
    SQLManager* sqlManager;
    StartWindow * startWindow;
};

#endif // DELETEPLAYER_H

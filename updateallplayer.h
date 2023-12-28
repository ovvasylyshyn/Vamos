#ifndef UPDATEALLPLAYER_H
#define UPDATEALLPLAYER_H

#include <QDialog>
#include "sqlmanager.h"
#include "Player.h"
#include <QMessageBox>
#include "startwindow.h"

namespace Ui {
class UpdateAllPlayer;
}

class UpdateAllPlayer : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateAllPlayer(QWidget *parent = nullptr);
    ~UpdateAllPlayer();

private slots:
    void on_updatePlayerPB_clicked();

private:
    Ui::UpdateAllPlayer *ui;
    SQLManager* sqlM;
};

#endif // UPDATEALLPLAYER_H

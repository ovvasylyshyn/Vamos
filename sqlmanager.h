#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <QSqlDatabase>
#include "dbmanager.h"
#include <sql.h>
#include "Player.h"
#include<QSqlQueryModel>
#include"photomodel.h"
#include <QDateTime>
#include "Coach.h"

#define DATABASE_HOST_NAME   "ExampleDataBase"
#define DATABASE_FILE_NAME   "DataBaseVamos.sqlite"
#define TABLE_REGISTRATION                  "registration"
#define TABLE_LOGIN              "login"
#define TABLE_PASSWORD              "password"
#define TABLE_NAME_PLAYER "player"
#define TABLE_NAME "name"
#define TABLE_SURNAME "surname"
#define TABLE_LASTNAME "lastName"
#define TABLE_AGE "age"
#define TABLE_ID "id"
#define TABLE_CONTRACTENDDATE "contractEndDate"
#define TABLE_NUMBER "number"
#define TABLE_CLUB "club"
#define TABLE_CLUBCONTRACTEXPIRY "clubContractExpiry"
#define TABLE_LEAGUE "league"
#define TABLE_PRICE "price"
#define TABLE_PREFFERED_FOOT "preferredFoot"
#define TABLE_FOOT_ID "id"
#define TABLE_FOOT_TYPE "footType"
#define TABLE_PREFERRED_FOOT_ID "footId"
#define TABLE_PHOTO "photo"

class SQLManager: public DBManager
{
    QSqlDatabase db;
    static SQLManager* instance;

public:
   static SQLManager* getInstance();
   void connectToDataBase() override;
   QSqlDatabase getDB() override;
   bool inserIntoTableRegistration(const QString login, QString password) override;
   bool inserIntoTablePlayer(const Player& player)override;
   SQLManager();
   bool openDataBase();
   bool restoreDataBase();
   void closeDataBase();
   bool createTables();
   bool userExists(const QString& login) const;
   bool login(QString login, QString password);
   PhotoModel* getAllPlayers();
   PhotoModel* getAllCoaches();
   QSqlQuery selectPlayerByPhotoOrName(const QString &value);
   bool deletePlayerFromTable(int playerId);
   bool deleteCoachFromTable(int coachId);
   bool inserIntoTableCoach(const Coach& coach)override;
   bool updatePlayer(const Player& player);
   bool updateCoach(const Coach& coach);
   bool updatePlayerC(const Player& player);
   bool UpdateCoachAll(const Coach& coach);
};

#endif // SQLMANAGER_H

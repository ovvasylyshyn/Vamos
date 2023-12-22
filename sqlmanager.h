#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <QSqlDatabase>
#include "dbmanager.h"
#include <sql.h>
#include "Player.h"
#include<QSqlQueryModel>
#include"photomodel.h"

#define DATABASE_HOST_NAME   "ExampleDataBase"
#define DATABASE_FILE_NAME   "DataBase3.sqlite"
#define TABLE_REGISTRATION                  "registration"
#define TABLE_LOGIN              "login"
#define TABLE_PASSWORD              "password"

#define TABLE_NAME_PLAYER "player"
#define TABLE_NAME_COACH "coach"
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
//Foot preferredFoot;


class SQLManager: public DBManager
{
    QSqlDatabase db;

    static SQLManager* instance;

    // Приватний конструктор


public:
    static SQLManager* getInstance();

    // Метод для підключення до бази даних
    void connectToDataBase() override;

    // Метод для отримання обробника (хендлера) підключення до БД
    QSqlDatabase getDB() override;

    // Метод для вставки записів у таблицю
   bool inserIntoTableRegistration(const QString login, QString password) override;
    bool inserIntoTablePlayer(const Player& player);

   SQLManager();
   bool openDataBase();
   bool restoreDataBase();
   void closeDataBase();
   bool createTables();
   bool userExists(const QString& login) const;
  // bool validateUser(const QString& login, const QString& password) const;
   void clearRegistrationTable();
   bool login(QString login, QString password);
 //  bool isUserRegistered(const QString& login);
   QString getLoginFromDatabase();
  // QSqlQueryModel* getAllPlayers();
   PhotoModel* getAllPlayers();
   QSqlQuery selectPlayerByPhotoOrName(const QString &value);
  // QSqlQuery searchPlayer(const QString &searchValue);
  // QSqlQuery searchPlayer(const  Player &player);
   bool updatePlayer(const Player& player);
};

#endif // SQLMANAGER_H

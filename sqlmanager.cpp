#include "sqlmanager.h"
#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QCryptographicHash>
#include <QSqlRecord>

//SQLManager::SQLManager()
//{

//}
SQLManager* SQLManager::instance = nullptr;

SQLManager::SQLManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOST_NAME);
    db.setDatabaseName(DATABASE_FILE_NAME);
}
SQLManager* SQLManager::getInstance() {
    if (instance == nullptr) {
        instance = new SQLManager();
    }
    return instance;
}
void SQLManager::connectToDataBase() {
    if (QFile(DATABASE_FILE_NAME).exists()) {
        this->openDataBase();
    } else {
        this->restoreDataBase();
    }
}
QSqlDatabase SQLManager::getDB() {
    return db;
}
bool SQLManager::restoreDataBase() {
    if (this->openDataBase()) {
        if (!this->createTables()) {
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не вдалось відновити базу даних";
        return false;
    }
}

bool SQLManager::openDataBase() {
    if (db.open()) {
        return true;
    } else
        return false;
}

void SQLManager::closeDataBase() {
    db.close();
}

bool SQLManager::createTables() {
    QSqlQuery query, query2,query3,query4,query5;

    if (!query.exec("CREATE TABLE " TABLE_REGISTRATION " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    TABLE_LOGIN    " VARCHAR(255) NOT NULL, "
                    TABLE_PASSWORD " VARCHAR(255) NOT NULL"
                    ")")) {
        qDebug() << "DataBase: error of create " << TABLE_REGISTRATION;
        qDebug() << query.lastError().text();
        return false;
    } else {
        qDebug() << "Table " << TABLE_REGISTRATION << " created successfully.";
    }

    if (!query2.exec("CREATE TABLE " TABLE_NAME_PLAYER " ("
                     TABLE_ID  " INTEGER PRIMARY KEY UNIQUE NOT NULL, "
                     TABLE_NAME " VARCHAR(255) NOT NULL, "
                     TABLE_SURNAME " VARCHAR(255) NOT NULL, "
                     TABLE_LASTNAME " VARCHAR(255) NOT NULL, "
                     TABLE_AGE " INTEGER NOT NULL, "
                     TABLE_CONTRACTENDDATE " DATE NOT NULL, "
                     TABLE_CLUBCONTRACTEXPIRY " DATE NOT NULL, "
                     TABLE_PREFFERED_FOOT " VARCHAR(255) NOT NULL, "
                     TABLE_LEAGUE " VARCHAR(255) NOT NULL, "
                     TABLE_CLUB " VARCHAR(255) NOT NULL, "
                     TABLE_NUMBER " INTEGER NOT NULL, "
                     TABLE_PRICE " INTEGER NOT NULL, "
                     TABLE_PHOTO " BLOB"
                     ")")) {
        qDebug() << "DataBase: error of create " << TABLE_NAME_PLAYER;
        qDebug() << query2.lastError().text();
        return false;
    } else {
        qDebug() << "Table " << TABLE_NAME_PLAYER << " created successfully.";
    }

if (!query3.exec("CREATE TABLE coach ("
                     TABLE_ID  " INTEGER PRIMARY KEY UNIQUE NOT NULL, "
                     TABLE_NAME " VARCHAR(255) NOT NULL, "
                     TABLE_SURNAME " VARCHAR(255) NOT NULL, "
                     TABLE_LASTNAME " VARCHAR(255) NOT NULL, "
                     TABLE_AGE " INTEGER NOT NULL, "
                     TABLE_CONTRACTENDDATE " DATE NOT NULL, "
                    "coach_contract_expiry DATE, "
                     "club VARCHAR(255), "
                                  "experience VARCHAR(255), "
                                  "type VARCHAR(255), "
                     "photo BLOB"
  ")")) {

        qDebug() << "DataBase: error of create " << "coach";
        qDebug() << query3.lastError().text();
        return false;
    } else {
        qDebug() << "Table coach created successfully.";
    }
    if (!query4.exec("CREATE TABLE deleteCoach ("
                     TABLE_ID  " INTEGER PRIMARY KEY UNIQUE NOT NULL, "
                     TABLE_NAME " VARCHAR(255) , "
                     TABLE_SURNAME " VARCHAR(255) , "
                     TABLE_LASTNAME " VARCHAR(255) , "
                     TABLE_AGE " INTEGER , "
                     TABLE_CONTRACTENDDATE " DATE , "
                     "coach_contract_expiry DATE, "
                     "club VARCHAR(255), "
                     "experience VARCHAR(255), "
                     "type VARCHAR(255), "
                     "photo BLOB"
                     ")")) {

        qDebug() << "DataBase: error of create " << "coach";
        qDebug() << query4.lastError().text();
        return false;
    } else {
        qDebug() << "Table coach created successfully.";
    }
    if (!query5.exec("CREATE TABLE deletePlayer ("
                     TABLE_ID  " INTEGER PRIMARY KEY UNIQUE NOT NULL, "
                     TABLE_NAME " VARCHAR(255) , "
                     TABLE_SURNAME " VARCHAR(255) , "
                     TABLE_LASTNAME " VARCHAR(255) , "
                     TABLE_AGE " INTEGER , "
                     TABLE_CONTRACTENDDATE " DATE , "
                     "coach_contract_expiry DATE, "
                     "club VARCHAR(255), "
                     "experience VARCHAR(255), "
                     "type VARCHAR(255), "
                     "photo BLOB"
                     ")")) {

        qDebug() << "DataBase: error of create " << "coach";
        qDebug() << query5.lastError().text();
        return false;
    } else {
        qDebug() << "Table coach created successfully.";
    }
    return true;
}

bool SQLManager::inserIntoTableRegistration(const QString login, QString password)
{
    QSqlQuery queryAccount;
    queryAccount.prepare("INSERT INTO " TABLE_REGISTRATION "("
                         TABLE_LOGIN " ,"
                         TABLE_PASSWORD " )"
                         "VALUES (:login, :password)");
    queryAccount.bindValue(":login", login);
    queryAccount.bindValue(":password", password);
    if (!queryAccount.exec()) {
        qDebug() << "error insert into " << TABLE_REGISTRATION;
        qDebug() << queryAccount.lastError().text();
        qDebug() << queryAccount.lastQuery();
        return false;
    } else
        return true;
}

bool SQLManager::inserIntoTablePlayer(const Player& player){
    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE_NAME_PLAYER " ("
                  TABLE_ID ", "
                  TABLE_NAME ", "
                  TABLE_SURNAME ", "
                  TABLE_LASTNAME ", "
                  TABLE_AGE ", "
                  TABLE_CONTRACTENDDATE ", "
                  TABLE_CLUBCONTRACTEXPIRY ", "
                  TABLE_PREFFERED_FOOT ", "
                  TABLE_LEAGUE ", "
                  TABLE_CLUB ", "
                  TABLE_NUMBER ", "
                  TABLE_PRICE ", "
                  TABLE_PHOTO " )"
                  "VALUES (:id, :name, :surname, :lastName, :age, :contractEndDate, :clubContractExpiry, :preferredFoot, :league, :club, :number, :price, :photo)");
    query.bindValue(":id",player.getId());
    query.bindValue(":name", QString::fromStdString(player.getName()));
    query.bindValue(":surname", QString::fromStdString(player.getSurName()));
    query.bindValue(":lastName", QString::fromStdString(player.getLastName()));
    query.bindValue(":age", player.getAge());
    query.bindValue(":contractEndDate", player.getContractEndDate().toString(Qt::ISODate));
    query.bindValue(":clubContractExpiry", player.getClubContractExpiry().toString(Qt::ISODate));
    query.bindValue(":preferredFoot", static_cast<int>(player.getPreferredFoot()));
    query.bindValue(":league", QString::fromStdString(player.getLeague()));
    query.bindValue(":club", QString::fromStdString(player.getClub()));
    query.bindValue(":number", player.getNumber());
    query.bindValue(":price", QString::number(player.getPrice()));
 query.bindValue(":photo", player.getPhotoData());
qDebug() << "Executing query: " << query.lastQuery();
    if (!query.exec()) {
        qDebug() << "Error inserting player into " << TABLE_NAME_PLAYER << " table";
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        return false;
    }
 return true;
}
bool SQLManager::inserIntoTableCoach(const Coach& coach){
 QSqlQuery query;
 query.prepare("INSERT INTO coach (id, name, surname, lastName, age, contractEndDate, coach_contract_expiry, club, experience, type, photo) "
               "VALUES (:id, :name, :surname, :lastName, :age, :contractEndDate, :coach_contract_expiry, :club, :experience, :type, :photo)");
 query.bindValue(":id", coach.getId());
 query.bindValue(":name", QString::fromStdString(coach.getName()));
 query.bindValue(":surname", QString::fromStdString(coach.getSurName()));
 query.bindValue(":lastName", QString::fromStdString(coach.getLastName()));
 query.bindValue(":age", coach.getAge());
 query.bindValue(":contractEndDate", coach.getContractEndDate().toString("yyyy-MM-dd"));
query.bindValue(":coach_contract_expiry", coach.getCoachContractExpiry().toString("yyyy-MM-dd"));
 query.bindValue(":club", QString::fromStdString(coach.getClub()));
 query.bindValue(":experience",coach.getExpirience());
 query.bindValue(":type", QString::fromStdString(coach.getType()));
 query.bindValue(":photo", coach.getPhotoData());
 qDebug() << "Executing query: " << query.lastQuery();
 if (!query.exec()) {
        qDebug() << "Error inserting coach into table: " << query.lastError().text();
        return false;
 } else {
        qDebug() << "Coach inserted successfully!";
        return true;
 }
}

bool SQLManager::inserIntoTableDeleteCoach(const Coach& coach){
 QSqlQuery query;
// query.prepare("INSERT INTO deleteCoach (name, surname, lastName, age, contractEndDate, coach_contract_expiry, club, experience, type, photo) "
//               "VALUES (:name, :surname, :lastName, :age, :contractEndDate, :coach_contract_expiry, :club, :experience, :type, :photo)");

// query.bindValue(":name", QString::fromStdString(coach.getName()));
// query.bindValue(":surname", QString::fromStdString(coach.getSurName()));
// query.bindValue(":lastName", QString::fromStdString(coach.getLastName()));
// query.bindValue(":age", coach.getAge());
// query.bindValue(":contractEndDate", coach.getContractEndDate().toString("yyyy-MM-dd"));
// query.bindValue(":coach_contract_expiry", coach.getCoachContractExpiry().toString("yyyy-MM-dd"));
// query.bindValue(":club", QString::fromStdString(coach.getClub()));
// query.bindValue(":experience",coach.getExpirience());
// query.bindValue(":type", QString::fromStdString(coach.getType()));
// query.bindValue(":photo", coach.getPhotoData());
  query.prepare("INSERT INTO deleteCoach (id, name, surname) "
                "VALUES (:id, :name, :surname)");

 query.bindValue(":id", coach.getId());
  query.bindValue(":name", QString::fromStdString(coach.getName()));
  query.bindValue(":surname", QString::fromStdString(coach.getSurName()));
 qDebug() << "Executing query: " << query.lastQuery();
 if (!query.exec()) {
        qDebug() << "Error inserting coach into table: " << query.lastError().text();
        return false;
 } else {
        qDebug() << "Coach inserted successfully!";
        return true;
 }
}

bool SQLManager::inserIntoTableDeletedPlayer(const Player& player){
 QSqlQuery query;
 query.prepare("INSERT INTO deletePlayer ("
               TABLE_ID ", "
               TABLE_NAME ", "
               TABLE_SURNAME ") "
//               TABLE_LASTNAME ", "
//               TABLE_AGE ", "
//               TABLE_CONTRACTENDDATE ", "
//               TABLE_CLUBCONTRACTEXPIRY ", "
//               TABLE_PREFFERED_FOOT ", "
//               TABLE_LEAGUE ", "
//               TABLE_CLUB ", "
//               TABLE_NUMBER ", "
//               TABLE_PRICE ", "
//               TABLE_PHOTO " )"
               "VALUES (:id, :name, :surname)");
 query.bindValue(":id",player.getId());
 query.bindValue(":name", QString::fromStdString(player.getName()));
 query.bindValue(":surname", QString::fromStdString(player.getSurName()));
// query.bindValue(":lastName", QString::fromStdString(player.getLastName()));
// query.bindValue(":age", player.getAge());
// query.bindValue(":contractEndDate", player.getContractEndDate().toString(Qt::ISODate));
// query.bindValue(":clubContractExpiry", player.getClubContractExpiry().toString(Qt::ISODate));
// query.bindValue(":preferredFoot", static_cast<int>(player.getPreferredFoot()));
// query.bindValue(":league", QString::fromStdString(player.getLeague()));
// query.bindValue(":club", QString::fromStdString(player.getClub()));
// query.bindValue(":number", player.getNumber());
// query.bindValue(":price", QString::number(player.getPrice()));
// query.bindValue(":photo", player.getPhotoData());
 qDebug() << "Executing query: " << query.lastQuery();
 if (!query.exec()) {
        qDebug() << "Error inserting player into " << TABLE_NAME_PLAYER << " table";
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        return false;
 }
 return true;
}

bool SQLManager::deletePlayerFromTable(int playerId, const QString name, const QString surname) {
 QSqlQuery query;
 query.prepare("DELETE FROM player WHERE id = :id AND name = :name AND surname = :surname");
 query.bindValue(":id", playerId);
 query.bindValue(":name", name);
 query.bindValue(":surname", surname);

 qDebug() << "Executing query: " << query.lastQuery();

 if (!query.exec()) {
        qDebug() << "Error deleting player from " << TABLE_NAME_PLAYER << " table";
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        return false;
 }
 if (query.numRowsAffected() == 0) {
        qDebug() << "Coach with ID " << playerId << " not found in coach table.";
        return false;
 }
 qDebug() << "Player with ID " << playerId << " deleted successfully from " << TABLE_NAME_PLAYER << " table.";
 return true;
}

bool SQLManager::deleteCoachFromTable(int coachId, const QString name, const QString surname) {
 QSqlQuery query;
 query.prepare("DELETE FROM coach WHERE id = :id AND name = :name AND surname = :surname");
 query.bindValue(":id", coachId);
 query.bindValue(":name", name);
 query.bindValue(":surname", surname);

 qDebug() << "Executing query: " << query.lastQuery();

 if (!query.exec()) {
        qDebug() << "Error deleting player from coach table";
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        return false;
 }
 if (query.numRowsAffected() == 0) {
        qDebug() << "Coach with ID " << coachId << " not found in coach table.";
        return false;
 }

 qDebug() << "Coach with ID " << coachId << " deleted successfully from coach table.";
 return true;
}

bool SQLManager::userExists(const QString& login) const {
    QSqlQuery query;
     query.prepare("SELECT COUNT(*) FROM " TABLE_REGISTRATION " WHERE login = :login");
    query.bindValue(":login", login);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return (count > 0);
    }
    return false;
}

bool SQLManager::login(QString login, QString password)
{
    QSqlQuery queryAccount;
    queryAccount.prepare("SELECT * FROM " TABLE_REGISTRATION " WHERE " TABLE_LOGIN " = :login AND " TABLE_PASSWORD
                         "= :password");
    queryAccount.bindValue(":login", login);
    queryAccount.bindValue(":password", password);
    queryAccount.exec();
    if (!queryAccount.exec()) {
        qDebug() << "error insert into " << TABLE_REGISTRATION;
        qDebug() << queryAccount.lastError().text();
        qDebug() << queryAccount.lastQuery();
    }
    if(queryAccount.next()) { return true;}
    else  {return false;}}

PhotoModel* SQLManager::getAllPlayers() {
    PhotoModel* model = new PhotoModel();
    model->setPhotoColumnIndex(1);

    QSqlQuery qry(db);
    qry.prepare("SELECT id, photo, surname, name FROM player");

    if (qry.exec()) {
        model->setQuery(qry);
    } else {
        qDebug() << "Error executing query: " << qry.lastError().text();
        delete model;
        model = nullptr;
    }

    return model;
}

PhotoModel* SQLManager::getAllCoaches() {
    PhotoModel* model = new PhotoModel();
    model->setPhotoColumnIndex(1);

    QSqlQuery qry(db);
    qry.prepare("SELECT id, photo, surname, name, age, contractEndDate, coach_contract_expiry, club, experience, type FROM coach");

    if (qry.exec()) {
        model->setQuery(qry);
    } else {
        qDebug() << "Error executing query: " << qry.lastError().text();
        delete model;
        model = nullptr;
    }

    return model;
}

QSqlQuery SQLManager::selectPlayerByPhotoOrName(const QString &value)
{
    QSqlQuery qry;
    if (openDataBase()) {
        qry.prepare("SELECT * FROM player WHERE photo = :val OR name = :val OR surname = :val");
        qry.bindValue(":val", value);
        if (!qry.exec()) {
            qDebug() << "error zapyt" << qry.lastError().text();
        }
    } else {
        qDebug() << "Помилка відкриття бази даних";
    }
    return qry;
}


bool SQLManager::updatePlayer(const Player& player) {
    QSqlQuery qry;
    qry.prepare("UPDATE player SET name=:name, surname=:surname, age=:age, clubContractExpiry=:clubContractExpiry, contractEndDate=:contractEndDate, club=:club, "
                "number=:number, league=:league, price=:price WHERE id=:id");
    qry.bindValue(":id", player.getId());
    qry.bindValue(":name", QString::fromStdString(player.getName()));
    qry.bindValue(":surname", QString::fromStdString(player.getSurName()));
    qry.bindValue(":age", player.getAge());
    qry.bindValue(":clubContractExpiry", player.getClubContractExpiry());
    qry.bindValue(":contractEndDate", player.getContractEndDate());
    qry.bindValue(":club", QString::fromStdString(player.getClub()));
    qry.bindValue(":number", player.getNumber());
    qry.bindValue(":league", QString::fromStdString(player.getLeague()));
    qry.bindValue(":price", player.getPrice());
    return qry.exec();
}

bool SQLManager::updateCoach(const Coach& coach) {
    QSqlQuery qry;
    qry.prepare("UPDATE coach SET name=:name, surname=:surname, contractEndDate=:contractEndDate WHERE id=:id");
    qry.bindValue(":id", coach.getId());
    qry.bindValue(":name", QString::fromStdString(coach.getName()));
    qry.bindValue(":surname", QString::fromStdString(coach.getSurName()));
    qry.bindValue(":contractEndDate", coach.getContractEndDate());
    return qry.exec();
}

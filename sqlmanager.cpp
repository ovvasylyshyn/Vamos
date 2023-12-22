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

// Метод для отримання екземпляру даного класу (патерн Singleton)
SQLManager* SQLManager::getInstance() {
    if (instance == nullptr) {
        instance = new SQLManager();
    }
    return instance;
}

// Метод для підключення до бази даних
void SQLManager::connectToDataBase() {
    /* Перед підключенням до бази даних виконуємо перевірку на її існування.
     * В залежності від результату виконуємо відкриття бази даних або її відновлення
     * */
    if (QFile(DATABASE_FILE_NAME).exists()) {
        this->openDataBase();
    } else {
        this->restoreDataBase();
    }
}

// Метод для отримання обробника підключення до БД
QSqlDatabase SQLManager::getDB() {
    return db;
}

// Метод відновлення бази даних
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

// Метод для відкриття бази даних
bool SQLManager::openDataBase() {
    if (db.open()) {
        return true;
    } else
        return false;
}

// Метод закриття бази даних
void SQLManager::closeDataBase() {
    db.close();
}

bool SQLManager::createTables() {
    QSqlQuery query, query2,query3;

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
                     TABLE_ID  " INTEGER PRIMARY KEY NOT NULL, "
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
                    // "FOREIGN KEY(" TABLE_PREFERRED_FOOT_ID ") REFERENCES " TABLE_FOOT " (" TABLE_FOOT_ID ")"
                     ")")) {
        qDebug() << "DataBase: error of create " << TABLE_NAME_PLAYER;
        qDebug() << query2.lastError().text();
        return false;
    } else {
        qDebug() << "Table " << TABLE_NAME_PLAYER << " created successfully.";
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
   // query.bindValue(":photo", player.getPhotoPath());
   // query.bindValue(":photo", QByteArray::fromRawData(player.getPhotoData().data(), player.getPhotoData().size()));

    query.bindValue(":photo", player.getPhotoData());
qDebug() << "Executing query: " << query.lastQuery();
    // query.bindValue(":photo", QByteArray::fromRawData(player.getPhotoData(), player.getPhotoSize()));
    if (!query.exec()) {
        qDebug() << "Error inserting player into " << TABLE_NAME_PLAYER << " table";
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        return false;
    }
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

    // Обробка помилок або повернення false, якщо щось пішло не так
    return false;
}

void SQLManager::clearRegistrationTable() {
    QSqlQuery countQuery;
    countQuery.exec("SELECT COUNT(*) FROM " TABLE_REGISTRATION);
    countQuery.next();
    int rowCount = countQuery.value(0).toInt();
    if (rowCount > 2) {
        QSqlQuery clearQuery;
        clearQuery.exec("DELETE FROM " TABLE_REGISTRATION);
    }
    QSqlQuery vacuumQuery;
    vacuumQuery.exec("VACUUM");
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

QString SQLManager::getLoginFromDatabase() {
    QSqlQuery query;
    query.prepare("SELECT * FROM " TABLE_REGISTRATION );

    if (query.exec() && query.next()) {
        QString userLogin = query.value("login").toString();
        return userLogin;
    }

    return QString();
}
//QSqlQueryModel* SQLManager::getAllPlayers() {
//    QSqlQueryModel* modal = new QSqlQueryModel();
//    QSqlQuery qry(db);

//    // Adjust the SQL query based on your database schema
//    qry.prepare("SELECT photo FROM player");
//    if (qry.exec()) {
//        modal->setQuery(qry);
//    } else {
//        qDebug() << "Error executing query: " << qry.lastError().text();
//    }

//    return modal;
//}
PhotoModel* SQLManager::getAllPlayers() {
    PhotoModel* model = new PhotoModel();
    model->setPhotoColumnIndex(0);  // Встановіть індекс стовпця з фотографіями

    QSqlQuery qry(db);
    qry.prepare("SELECT photo, surname, name FROM player");

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
            qDebug() << "Помилка виконання запиту:" << qry.lastError().text();
        }
      // closeDataBase();
    } else {
        qDebug() << "Помилка відкриття бази даних";
    }
    return qry;
}

//QSqlQuery SQLManager::searchPlayer(const  Player &player)
//{
//    QSqlQuery query;
//    if (openDataBase()) {
//        query.prepare("SELECT * FROM player WHERE "
//                    "id = :id OR "
//                    "name = :name OR "
//                    "surname = :surname OR "
//                    "lastName = :lastName OR "
//                    "age = :age OR "
//                    "contractEndDate = :contractEndDate OR "
//                    "clubContractExpiry = :clubContractExpiry OR "
//                    "preferredFoot = :preferredFoot OR "
//                    "league = :league OR "
//                    "club = :club OR "
//                    "number = :number OR "
//                    "price = :price");
//        query.bindValue(":id", player.getId());
//        query.bindValue(":name", player.getName());
//        query.bindValue(":surname", player.getSurName());
//        query.bindValue(":lastName", player.getLastName());
//        query.bindValue(":contractEndDate", player.getContractEndDate());
//        query.bindValue(":clubContractExpiry", player.getClubContractExpiry());
//        query.bindValue(":preferredFoot", player.getPreferredFoot());
//        query.bindValue(":league", player.getLeague());
//        query.bindValue(":club", player.getClub());
//           query.bindValue(":number", player.getNumber());
//              query.bindValue(":price", player.getPrice());

//           query.exec();
//           return query;

//    QSqlQuery qry;
//    if (openDataBase()) {
//        qry.prepare("SELECT * FROM player WHERE photo = :val OR name = :val");
//        qry.bindValue(":val", searchValue);
//        closeDataBase();
//    } else {
//        qDebug() << "Помилка відкриття бази даних";
//    }
//    return qry;
//}

//bool SQLManager::updatePlayer(const QString& id, const QString& name, const QString& surname, const QString& contractEndDate) {
//    QSqlQuery qry;
//    qry.prepare("UPDATE player SET name=:name, surname=:surname, contractEndDate=:contractEndDate WHERE id=:id");
//    qry.bindValue(":id", id);
//    qry.bindValue(":name", name);
//    qry.bindValue(":surname", surname);
//    qry.bindValue(":contractEndDate", contractEndDate);

//    return qry.exec();
//}
bool SQLManager::updatePlayer(const Player& player) {
    QSqlQuery qry;
    qry.prepare("UPDATE player SET name=:name, surname=:surname, contractEndDate=:contractEndDate WHERE id=:id");
    qry.bindValue(":id", player.getId());
    qry.bindValue(":name", QString::fromStdString(player.getName()));
    qry.bindValue(":surname", QString::fromStdString(player.getSurName()));
    qry.bindValue(":contractEndDate", player.getContractEndDate());

    return qry.exec();
}

#ifndef DBMANAGER_H
#define DBMANAGER_H
#include "Coach.h"
#include "Player.h"

class DBManager
{
public:

    // Суто віртуальний метод для підключення до бази даних
    virtual void connectToDataBase() = 0;

    // Суто віртуальний метод для отримання обробника (хендлера) підключення до БД
    virtual QSqlDatabase getDB() = 0;

    // Суто віртуальний метод для вставки записів у таблицю
   virtual bool inserIntoTableRegistration(const QString login, QString password)=0;
   virtual  bool inserIntoTableCoach(const Coach& coach)=0;
   virtual   bool inserIntoTablePlayer(const Player& player)=0;
};

#endif // DBMANAGER_H

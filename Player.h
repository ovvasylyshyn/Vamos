#pragma once
#include "People.h"
#include <chrono>
#include <QByteArray>
#include <QDate>

enum class Foot {
    LEFT,
    RIGHT,
    BOTH
};

class Player :
    public People
{ public:
    Player() = default;
    Player(int id, const string& name, const string& surname, const string& lastName,
        int age, const QDate& contractEndDate,  const QDate& clubContractExpiry,
        Foot preferredFoot, const string& league,
        const string& club, int number,double price, const QByteArray& photoData);

 
    int getNumber() const;
    string getClub() const;
   // chrono::system_clock::time_point getClubContractExpiry() const;
    QDate getClubContractExpiry() const;
    Foot getPreferredFoot() const;
    string getLeague() const;
    double getPrice() const;
     QByteArray getPhotoData() const;
    int getPhotoSize() const;
  QString getPhotoPath() const;



    void setNumber(int number);
    void setClub(const string& club);
    void setContractExpiry(const QDate& clubContractExpiry);
    //void setContractExpiry(const chrono::system_clock::time_point& clubContractExpiry);
    void setPreferredFoot(Foot preferredFoot);
    void setLeague(const string& league);
    void setPrice(double price);
    void setPhotoData(const QByteArray& photoData);
    void setPhotoSize(int photoSize);
  //  void setPhotoPath(const QString& photoPath);
   // void Player::setPhotoPath(const QString& photoPath) { this->photoPath = photoPath; }
private:
    int number;
    string club;
   // chrono::system_clock::time_point clubContractExpiry;
    Foot preferredFoot;
    string league;
    double price;
    QByteArray photoData;
    int photoSize;
    QDate contractEndDate;
    QDate clubContractExpiry;
     QString photoPath;

};


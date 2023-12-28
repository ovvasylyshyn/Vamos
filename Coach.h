#pragma once
#include "People.h"
#include <QDate>
#include <QByteArray>
class Coach :
    public People
{
    string club, type;
    int expirience;
    QDate coachContractExpiry;
    QString photoPath;
    QByteArray photoData;
    int photoSize;

public:

    Coach() = default;
    Coach(const string& name, const string& surname, 
        const string& lastName, int age, int id,
        const chrono::system_clock::time_point& contractEndDate,
        const string& club, chrono::system_clock::time_point coachContractExpiry);

    string getClub() const;
    int getExpirience() const;
    string getType() const;
    QDate getCoachContractExpiry() const;
    QString getPhotoPath() const;
    QByteArray getPhotoData() const;
    int getPhotoSize() const;
    void setClub(const string& newClub);
    void setExpirience(int newExpirience);
    void setType(const string& newType);
    void setCoachContractExpiry(const QDate& newCoachContractExpiry);
    void setPhotoPath(const QString& newPhotoPath);
    void setPhotoData(const QByteArray& newPhotoData);
    void setPhotoSize(int newPhotoSize);
};


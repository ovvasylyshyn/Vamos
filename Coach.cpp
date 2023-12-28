#include "Coach.h"
string Coach:: getClub() const {
    return club;
}

int Coach::getExpirience() const {
    return expirience;
}

string Coach::getType() const {
    return type;
}

QDate Coach:: getCoachContractExpiry() const {
    return coachContractExpiry;
}

QString Coach:: getPhotoPath() const {
    return photoPath;
}

QByteArray Coach:: getPhotoData() const {
    return photoData;
}

int  Coach::getPhotoSize() const {
    return photoSize;
}

void Coach::setClub(const string& newClub) {
    club = newClub;
}

void Coach::setExpirience(int newExpirience) {
    expirience = newExpirience;
}

void Coach::setType(const string&  newType) {
    type = newType;
}

void Coach::setCoachContractExpiry(const QDate& newCoachContractExpiry) {
    coachContractExpiry = newCoachContractExpiry;
}

void Coach::setPhotoPath(const QString& newPhotoPath) {
    photoPath = newPhotoPath;
}

void Coach::setPhotoData(const QByteArray& newPhotoData) {
    photoData = newPhotoData;
}

void Coach::setPhotoSize(int newPhotoSize) {
    photoSize = newPhotoSize;
}

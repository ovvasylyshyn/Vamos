#include "Player.h"

Player::Player (int id, const string& name, const string& surname, const string& lastName,
               int age, const QDate& contractEndDate,  const QDate& clubContractExpiry,
               Foot preferredFoot, const string& league,
               const string& club, int number,double price, const QByteArray& photoData)
    : People(name, surname, lastName, age, id, contractEndDate),
    number(number), club(club), clubContractExpiry(clubContractExpiry),
    preferredFoot(preferredFoot), league(league), price(price), photoData(photoData) {}


int Player::getNumber() const {
	return number;
}
string Player::getClub() const {
	return club;
}
QDate Player::getClubContractExpiry() const {
    return clubContractExpiry;
}

Foot Player::getPreferredFoot() const {
	return preferredFoot;
}
string Player::getLeague() const {
	return league;
}
double Player::getPrice() const {
	return price;
}
int Player:: getPhotoSize() const{
    return photoSize;
}
 QByteArray Player::getPhotoData() const {
    return photoData;
}
void Player::setNumber(int number) {
	this->number = number;
}
void  Player::setClub(const string& club) {
	this->club = club;
}

void Player::setContractExpiry(const QDate& clubContractExpiry) {
    this->clubContractExpiry = clubContractExpiry;
}
void  Player::setPreferredFoot(Foot preferredFoot) {
	this->preferredFoot = preferredFoot;
}
void  Player::setLeague(const string& league) {
	this->league = league;
}
void  Player:: setPrice(double price) {
	this->price = price;
}
void Player::setPhotoData(const QByteArray& photoData){
    this->photoData=photoData;
}
void Player:: setPhotoSize(int photoSize){
    this->photoSize=photoSize;
}

#include "People.h"
//People::People() :name(nullptr), surname(nullptr), lastName(nullptr), age(0), id(0), contractEndDate(0) {};
People::People(const string& name, const string& surname, const string& lastName, int age, int id, const QDate& contractEndDate)
    : name(name), surname(surname), lastName(lastName), age(age),id(id), contractEndDate(contractEndDate) {}

string People::getName() const {
    return name;
}

string People::getSurName()const {
    return surname;
}

string People::getLastName() const {
    return lastName;
}

int People::getAge() const {
    return age;
}

int People::getId() const{
    return id;
}

//chrono::system_clock::time_point People::getContractEndDate() const {
//    return contractEndDate;
//}

QDate People::getContractEndDate() const {
    return contractEndDate;
}

void People:: setName(const string& name) {
    this->name = name;
}
void People::setSurName(const string& surname) {
    this->surname = surname;
}
void People::setLastName(const string& lastName) {
    this->lastName = lastName;
}
void People::setAge(int age) {
    this->age = age;
}
void People::setId(int id) {
    this->id = id;
}
//void People::setContractEndDate(const chrono::system_clock::time_point& contractEndDate) {
//    this->contractEndDate = contractEndDate;
//}
void People::setContractEndDate(const QDate& contractEndDate) {
    this->contractEndDate = contractEndDate;
}

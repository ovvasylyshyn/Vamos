#pragma once
#include <iostream>
#include <chrono>
#include <QDate>
using namespace std;
class People
{
	string name, surname, lastName;
	int age, id;
    QDate contractEndDate;
    //chrono::system_clock::time_point contractEndDate;

public: 
	People() = default;
    People(const string& name, const string& surname, const string& lastName, int age, int id, const QDate& contractEndDate);
    
    string getName() const;
    string getSurName() const;
    string getLastName() const;
    int getAge() const;
    int getId()const;
    QDate getContractEndDate() const;

   // chrono::system_clock::time_point getContractEndDate() const;

    void setName(const string& name);
    void setSurName(const string& surname);
    void setLastName(const string& lastName);
    void setAge(int age);
    void setId(int id);
    void setContractEndDate(const QDate& contractEndDate);
   // void setContractEndDate(const chrono::system_clock::time_point& contractEndDate);
};


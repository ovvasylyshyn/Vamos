#pragma once
#include "People.h"
class Coach :
    public People
{
    string club;
    chrono::system_clock::time_point coachContractExpiry;
public:

    Coach() = default;
    Coach(const string& name, const string& surname, 
        const string& lastName, int age, int id,
        const chrono::system_clock::time_point& contractEndDate, 
        const string& club, chrono::system_clock::time_point coachContractExpiry);

    const string& getClub() const;
    void setClub(const string& Club);

    const chrono::system_clock::time_point& getCoachContractExpiry() const;
    void setCoachContractExpiry(const chrono::system_clock::time_point& coachContractExpiry);

};


#include "user.h"

std::string User::getName() const {
    return name;
}

User::User(std::string name, std::string email, std::string phone, std::string department, int age)
{
    this->name = name;
    this->email = email;
    this->phone = phone;
    this->department = department;
    this->age = age;
}

User::User(std::string name, std::string email, std::string phone, int age)
{
    this->name = name;
    this->email = email;
    this->phone = phone;
    this->age = age;
}

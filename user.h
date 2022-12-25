#ifndef USER_H
#define USER_H

#include<iostream>

class User{
private:
        std::string name;
        std::string email;
        std::string phone;
        std::string department;
        int age;
public:
    User(std::string name,
    std::string email,
    std::string phone,
    std::string department,
         int age);

    User(std::string name,
    std::string email,
    std::string phone,
         int age);

    std::string getName() const;
    std::string getEmail() const;
    std::string getPhone() const;
    std::string getDepartment() const;
    int getAge() const;
};

#endif // USER_H

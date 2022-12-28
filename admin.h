#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>
#include "QDateTime"
#include "user.h"
class Admin : public User{

private:
    int ID;
    std::string speciality;
    std::string title;
    std::string password;
    QDateTime creation_date;
    std::string biography;


public:
    Admin(
        std::string name,
        std::string speciality,
        std::string title,
        std::string email,
        std::string password,
        std::string phone,
        std::string biography,
        int age,
        QDateTime creation_date);

    int get_id();
    std::string get_speciality() const;
    std::string get_title() const;
    std::string get_password() const;
    QDateTime get_creation_date();
    std::string get_biography() const;
    int get_dateOfbirth() const;


};

#endif // ADMIN_H

#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>
#include "QDateTime"
#include "user.h"
class Admin : public User{

private:

    std::string speciality;
    std::string title;
    QDateTime creation_date;
    std::string biography;


public:
    Admin(
        std::string name,
        std::string speciality,
        std::string title,
        std::string email,
        std::string phone,
        std::string biography,
        int age,
        QDateTime creation_date);

};

#endif // ADMIN_H

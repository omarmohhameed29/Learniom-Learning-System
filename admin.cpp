#include "admin.h"

Admin::Admin(
        std::string name,
        std::string speciality,
        std::string title,
        std::string email,
        std::string phone,
        std::string biography,
        int age,
        QDateTime creation_date)
        : User(name, email, phone, age)

{
    this->title = title;
    this->biography = biography;
    this->speciality = speciality;
    this->creation_date = creation_date;

}

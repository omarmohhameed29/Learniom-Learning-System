#include "admin.h"
static int code=0;

Admin::Admin(
        std::string name,
        std::string speciality,
        std::string title,
        std::string email,
        std::string password,
        std::string phone,
        std::string biography,
        int age,
        QDateTime creation_date)
        : User(name, email, phone, age)

{
    this->title = title;
    this->biography = biography;
    this->password = password;
    this->speciality = speciality;
    this->creation_date = creation_date;
    this->ID = ++code;
};


    std::string Admin::get_speciality() const{
        return title;
    }

    std::string Admin::get_title() const{
        return title;
    }

    std::string Admin::get_password() const{
        return password;
    }

    QDateTime Admin::get_creation_date() {
        return creation_date;

    }

    std::string Admin::get_biography() const{
        return biography;

    }

    int Admin::get_id()
    {
        return this->ID;
    }


    int Admin::get_dateOfbirth() const
    {
        return 2023-getAge() ; //function to get date of birth
    }




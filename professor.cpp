#include "professor.h"
static int code=0;
Professor::Professor(
        std::string name,
        std::string email,
        std::string phone,
        std::string department,
        std::string phd,
        std::string honors,
        std::string additional,
        std::string graduated_from,
        int age,
        QDateTime joined_on)
        : User(name, email, phone, department, age)
{
    this->phd = phd;
    this->honors = honors;
    this->additional = additional;
    this->graduated_from = graduated_from;
    this->joined_on = joined_on;
    this->ID = ++code;

}


int Professor :: get_id(){
    return this->ID;
}

std::string Professor :: get_phd(){
    return phd;
}

std::string Professor :: get_honors(){
    return honors;
}

std::string Professor :: get_additional(){
    return additional;
}


std::string Professor :: get_graduated_from(){
    return graduated_from;
}

QDateTime Professor :: get_joined_on(){
    return joined_on;
}




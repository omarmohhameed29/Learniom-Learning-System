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

#include "student.h"

Student::Student(
        std::string name,
        std::string code,
        std::string email,
        std::string phone,
        std::string department,
        int age,
        int graduation_year,
        std::vector<Course*> courses)
        : User(name, code, email, phone, department, age)
{
    this->graduation_year = graduation_year;
    this->courses = std::vector<Course*>();
};

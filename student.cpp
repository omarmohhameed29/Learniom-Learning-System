#include "student.h"
static int code=0;
int Student::getGraduation_year() const
{
    return graduation_year;
}

Student::Student(
        std::string name,
        std::string email,
        std::string phone,
        std::string department,
        int age,
        int graduation_year)
        : User(name, email, phone, department, age)
{
    this->graduation_year = graduation_year;
    this->courses = std::vector<Course*>();
    this->ID = ++code;
};

int Student::get_id()
{
    return this->ID;
}

std::vector<Course*> Student::get_courses()
{
    return this->courses;
}

void Student::set_courses(std::vector<Course*> course)
{
    this->courses = course;
}

std::map<Course*, float> Student::get_courses_grades()
{
    return this->courses_grades;
}

void Student::set_courses_grades(std::map<Course*, float> courses_grades)
{
    this->courses_grades = courses_grades;
}


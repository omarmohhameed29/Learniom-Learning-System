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
    this->ID = ++code;
};

int Student::get_id()
{
    return this->ID;
}

std::vector<std::string> Student::get_courses()
{
    return this->courses;
}

void Student::set_courses(std::string course)
{
    this->courses.push_back(course);
}

std::map<std::string, float> Student::get_courses_grades()
{
    return this->courses_grades;
}

void Student::set_courses_grades(std::string course , float grade)
{
    this->courses_grades[course] = grade;
}


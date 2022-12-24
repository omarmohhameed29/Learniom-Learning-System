#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include "user.h"

class Course;


class Student : public User {

private:
    int ID;
    int graduation_year;
    std::vector<Course*> courses;

public:
    Student(
        std::string name,
        std::string email,
        std::string phone,
        std::string department,
        int age,
        int graduation_year);
};

#endif // STUDENT_H

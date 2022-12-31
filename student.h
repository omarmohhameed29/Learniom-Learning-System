#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include "user.h"
#include "map"
class Course;


class Student : public User {

private:
    int ID;
    int graduation_year;
    std::vector<Course*> courses;
    std::map<Course*, float> courses_grades;

public:
    Student(
        std::string name,
        std::string email,
        std::string phone,
        std::string department,
        int age,
        int graduation_year);

    int get_id();
    int getGraduation_year() const;
    std::vector<Course*> get_courses();
    void set_courses(std::vector<Course*>);
    std::map<Course*, float> get_courses_grades();
    void set_courses_grades(std::map<Course*, float> courses_grades);


};

#endif // STUDENT_H

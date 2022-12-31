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
    std::vector<std::string> courses;
    std::map<std::string, float> courses_grades;

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
    std::vector<std::string> get_courses();
    void set_courses(std::string course);
    std::map<std::string, float> get_courses_grades();
    void set_courses_grades(std::string course , float grade);


};

#endif // STUDENT_H

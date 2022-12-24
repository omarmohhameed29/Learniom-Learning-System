#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <iostream>
#include "QDateTime"
#include <vector>
#include "user.h"
class Course;

class Professor: public User
{
private:
    int ID;
    std::string phd;
    std::string honors;
    std::string additional;
    std::string graduated_from;
    QDateTime joined_on;
    std::vector<Course*> courses;
public:

    Professor(
        std::string name,
        std::string email,
        std::string phone,
        std::string department,
        std::string phd,
        std::string honors,
        std::string additional,
        std::string graduated_from,
        int age,
        QDateTime joined_on);
};

#endif // PROFESSOR_H

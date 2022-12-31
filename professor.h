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
    std::string joined_on;
    std::string birth;
    std::vector<std::string> courses;
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
        std::string birth,
        std::string joined_on);


   int get_id();
   std::string get_phd();
   std::string get_honors();
   std::string get_additional();
   std::string get_graduated_from();
   std::string get_joined_on();
   std::string get_birth();
   std::vector<std::string> get_courses();
   void set_courses(std::string course);

};

#endif // PROFESSOR_H

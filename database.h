#ifndef DATABASE_H
#define DATABASE_H

#include"admin.h"
#include "student.h"
#include "professor.h"
#include "course.h"

class Database {
public:
    std::vector<Admin*> admins;
    std::vector<Student*> students;
    std::vector<Professor*> professors;
    std::vector<Course*> courses;

    Database();
};

#endif // DATABASE_H

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

    // For testing
    std::vector<Student*> get_students_mock_data() {
        return {
            new Student("Amir Hesham", "amirhesham65@gmail.com", "01013708540", "SBE", 20, 2025),
            new Student("Karim Hesham", "testthing@gmail.com", "01013708540", "CMP", 20, 2025),
            new Student("Mohamed Alaa", "moalaaaaaaa@gmail.com", "01013708540", "SBE", 20, 2025),
            new Student("John Doe", "amirhesham65@gmail.com", "01013708540", "SBE", 20, 2025),
            new Student("Jane Doe", "amirhesham65@gmail.com", "01013708540", "CMP", 20, 2025)
        };
    };

};

#endif // DATABASE_H

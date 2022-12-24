#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <vector>
#include <map>
#include <QDateTime>
#include "student.h"
#include "professor.h"

/// \brief The WeekDay enum
/// Representing the week days as discrete enumeration
enum WeekDay { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY };

/// \brief The CourseType enum
/// Representing two types of course
/// 1. MANDATORY - A course which the student must take
/// 2. Elective - A course which  the student may take
enum CourseType { MANDATORY, ELECTIVE };

class Course {
private:
    std::string name;
    std::string code;
    std::string department;
    std::string category;
    std::string hall;
    WeekDay day;
    CourseType type;
    QDateTime start_time;
    QDateTime end_time;
    int academic_year;
    std::vector<Student*> students;
    std::vector <Professor*> professors;
    std::map<Student*, float> students_grades;

public:
    Course(std::string name,
           std::string code,
           std::string department,
           std::string category,
           std::string hall,
           WeekDay day,
           CourseType type,
           QDateTime start_time,
           QDateTime end_time,
           int academic_year);

    /// \brief add_student
    /// Add a given student into the students vector in the course
    /// \param student - The student to be added
    void add_student(Student*);

    /// \brief delete_student
    /// Remove a given student from the students vector in the course
    /// \param student - The student to be removed
    void delete_student(Student*);

    /// \brief find_student_by_name
    /// Search for a student with a given name in the students vector in the course
    /// \param string -  The student name to be found
    /// \return student -
    Student* find_student_by_name(std::string);

    // Edit the grade of a given student in the students_grades map
    void edit_student_grade(Student*, float);

    // Add a given professor into the professors vector in the course
    void add_professor(Professor*);

    // Remove a given professor from the professors vector in the course
    void delete_professor(Professor*);

    // Search for a professor with a given name in the professors vector in the course
    Professor* find_professor_by_name(std::string);

};

#endif // COURSE_H

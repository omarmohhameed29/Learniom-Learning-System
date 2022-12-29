#include <algorithm>
#include "course.h"

Course::Course(std::string name,
       std::string code,
       std::string department,
       std::string category,
       std::string hall,
       WeekDay day,
       CourseType type,
       QDateTime start_time,
       QDateTime end_time,
       int academic_year)
{
    this->name = name;
    this->code = code;
    this->department = department,
    this->category = category;
    this->hall = hall;
    this->day = day;
    this->type = type;
    this->start_time = start_time;
    this->end_time = end_time;
    this->academic_year = academic_year;

    students = std::vector<Student*>();
    professors = std::vector<Professor*>();
    students_grades = std::map<Student*, float>();
};

void Course::add_student(Student* student) {
    students.push_back(student);
}

void Course::delete_student(Student* student) {
    students.erase(std::remove(students.begin(), students.end(), student), students.end());
}

Student* Course::find_student_by_name(std::string name) {
    for (int i = 0; i < students.size(); i++) {
        Student* curr = students[i];
        if (curr->getName() == name) {
            return curr;
        }
    }
    return NULL;
}

void Course::edit_student_grade(Student* student, float grade) {
    students_grades[student] = grade;
}

void Course::add_professor(Professor* professor){
    professors.push_back(professor);
}

void Course::delete_professor(Professor* professor) {
    professors.erase(std::remove(professors.begin(), professors.end(), professor), professors.end());
}

Professor* Course::find_professor_by_name(std::string name){
    for (int i = 0; i < professors.size(); i++) {
        Professor* curr = professors[i];
        if (curr->getName() == name) {
            return curr;
        }
    }
    return NULL;
}

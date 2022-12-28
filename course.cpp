#include <algorithm>
#include "course.h"
static int course_code = 0;

// code to be added
// week day to be edited
// type to be edited
Course::Course(int ID,
        std::string name,
       std::string department,
       std::string category,
       std::string hall,
       std::string day,
       std::string type,
       QDateTime start_time,
       QDateTime end_time,
       int academic_year)
{
    this->name = name;
    this->code = 001;
    this->department = department,
    this->category = category;
    this->hall = hall;
    this->day = day;
    this->type = type;
    this->start_time = start_time;
    this->end_time = end_time;
    this->academic_year = academic_year;
    this->ID = ++course_code;

    students = std::vector<Student*>();
    professors = std::vector<Professor*>();
    students_grades = std::map<Student*, float>();
};

std::string Course::get_name() const {
    return name;
}

std::string Course::get_code() const {
    return code;
}

std::string Course::get_department() const {
    return department;
}

std::string Course::get_category() const {
    return category;
}

std::string Course::get_hall() const {
    return hall;
}

std::string Course::get_type() const {
    return type;
}

int Course::get_academic_year() const {
    return academic_year;
}

int Course::get_ID() const {
    return ID;
}
// to be edited later
int Course::get_num_std() const {
    return 500;

}

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

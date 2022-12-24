#include "database.h"

Database::Database() {
    admins = std::vector<Admin*>();
    students = std::vector<Student*>();
    professors = std::vector<Professor*>();
    courses = std::vector<Course*>();
}

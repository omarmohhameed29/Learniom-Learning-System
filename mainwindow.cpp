#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cmath>
#include <stack>

#include "validate.h"
#include "student.h"
#include "database.h"
#include "admin.h"


// Handle Navigation as Single Page Application (SPA)
// Using a stack and a StackedWidget
std::stack<int> navigation_stack;

int push_navigation(int page_number) {
    navigation_stack.push(page_number);
    return page_number;
}

int pop_navigation() {
    navigation_stack.pop();
    return navigation_stack.top();;
}

void clear_navigation() {
    while (navigation_stack.size() > 1) {
        navigation_stack.pop();
    }
}

Database* database;

// TODO: move to student class ::: Keep as it is
std::map<std::string, QString> get_student_data_as_qstrings(Student* student) {
    std::map<std::string, QString> result;

    result["id"] = QString::fromStdString(std::to_string(student->get_id()));
    result["name"] = QString::fromStdString(student->getName());
    result["email"] = QString::fromStdString(student->getEmail());
    result["department"] = QString::fromStdString(student->getDepartment());
    result["year"]= QString::fromStdString(std::to_string(student->getGraduation_year()));
    result["phone"] = QString::fromStdString(student->getPhone());
    return result;
}

std::map<std::string, QString> get_admin_data_as_qstrings(Admin* admin) {
    std::map<std::string, QString> result;

    result["id"] = QString::fromStdString(std::to_string(admin->get_id()));
    result["name"] = QString::fromStdString(admin->getName());
    result["email"] = QString::fromStdString(admin->getEmail());
    result["speciality"] = QString::fromStdString(admin->get_speciality());
    result["title"]= QString::fromStdString(admin->get_title());
    result["phone"] = QString::fromStdString(admin->getPhone());
    result["password"] = QString::fromStdString(admin->get_password());
    result["biography"] = QString::fromStdString(admin->get_biography());

    return result;
}




// TODO: RENAME THOSE IMMED.

//Global variable keeps track of current clicked row index in the QTableWidget
//In order to control the delete button and the save button
int row_index_student = NULL;
int row_index_admin = NULL;


//Helper Function that takes the current clicked row index in the QTableWidget
//And passes its value to the global variable above
void store_row_index(int row){
    row_index_student = row;
}

void store_row_index_admin(int row){
    row_index_admin = row;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    // Initialize the database mock
    database = new Database();

    // Inject mock data
    database->students = database->get_students_mock_data();


    // Remove layout margin to fix the app bar to the top
    ui->ContainerView->layout()->setContentsMargins(0, 0, 0, 0);

    // Navigate to the login page on starting up
    ui->ViewStack->setCurrentIndex(push_navigation(0));

    // Hiding app bar buttons on starting up
    ui->btn_logout_1->setVisible(false);
    ui->btn_back->setVisible(false);

    // Setting up students table
    QHeaderView* students_table_header = ui->tbl_students->horizontalHeader();
    students_table_header->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

    int tbl_students_rows_count = database->students.size();
    ui->tbl_students->setRowCount(tbl_students_rows_count);
    ui->tbl_students->verticalHeader()->setVisible(false);
    ui->tbl_students->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (auto row = 0; row < tbl_students_rows_count; row++) {
        auto student_data = get_student_data_as_qstrings(database->students.at(row));

        ui->tbl_students->setItem(row, 0, new QTableWidgetItem(student_data["id"]));
        ui->tbl_students->setItem(row, 1, new QTableWidgetItem(student_data["name"]));
        ui->tbl_students->setItem(row, 2, new QTableWidgetItem(student_data["email"]));
        ui->tbl_students->setItem(row, 3, new QTableWidgetItem(student_data["department"]));
        ui->tbl_students->setItem(row, 4, new QTableWidgetItem(student_data["year"]));
    }

    // Setting up professors table
    QHeaderView* professors_table_header = ui->tbl_professors->horizontalHeader();
    professors_table_header->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

    // Setting up admins table
    QHeaderView* admins_table_header = ui->tbl_admins->horizontalHeader();
    admins_table_header->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

    int tbl_admins_rows_count = database->admins.size();
    ui->tbl_admins->setRowCount(tbl_admins_rows_count);
    ui->tbl_admins->verticalHeader()->setVisible(false);
    ui->tbl_admins->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (auto row = 0; row < tbl_admins_rows_count; row++) {
        auto admin_data = get_admin_data_as_qstrings(database->admins.at(row));

        ui->tbl_admins->setItem(row, 0, new QTableWidgetItem(admin_data["id"]));
        ui->tbl_admins->setItem(row, 1, new QTableWidgetItem(admin_data["name"]));
        ui->tbl_admins->setItem(row, 2, new QTableWidgetItem(admin_data["title"]));
        ui->tbl_admins->setItem(row, 3, new QTableWidgetItem(admin_data["email"]));
        ui->tbl_admins->setItem(row, 4, new QTableWidgetItem(admin_data["phone"]));
    }







}

MainWindow::~MainWindow() {
    delete ui;
}

// App Bar
void MainWindow::on_btn_logout_1_clicked() {
    clear_navigation();
    ui->ViewStack->setCurrentIndex(0);
    ui->btn_back->setVisible(false);
    ui->btn_logout_1->setVisible(false);
}

void MainWindow::on_btn_back_clicked() {
    // Correctly hiding the app bar buttons on the login page on going back
    if (navigation_stack.top() == 0) {
        ui->btn_back->setVisible(false);
        ui->btn_logout_1->setVisible(false);
    } else {
        ui->ViewStack->setCurrentIndex(pop_navigation());
        if (navigation_stack.top() == 0) {
            ui->btn_back->setVisible(false);
            ui->btn_logout_1->setVisible(false);
        }
    }
}

// P0_Login
void MainWindow::on_btn_login_clicked() {
    ui->btn_back->setVisible(true);
    ui->ViewStack->setCurrentIndex(push_navigation(1));
    ui->btn_logout_1->setVisible(true);
}

void MainWindow::on_btn_logout_2_clicked() {
    clear_navigation();
    ui->ViewStack->setCurrentIndex(0);
    ui->btn_back->setVisible(false);
    ui->btn_logout_1->setVisible(false);
}


// P1_Dashboard
void MainWindow::on_btn_nav_students_clicked() {
    ui->ViewStack->setCurrentIndex(push_navigation(2));
}

void MainWindow::on_btn_nav_professors_clicked() {
    ui->ViewStack->setCurrentIndex(push_navigation(4));
}

void MainWindow::on_btn_nav_admins_clicked() {
    ui->ViewStack->setCurrentIndex(push_navigation(7));
}

// P2_Students
void MainWindow::on_btn_add_student_clicked() {
    ui->ViewStack->setCurrentIndex(push_navigation(3));
}

// P3_Add_Student
void MainWindow::on_btn_add_student_form_clicked() {
    validate valid;

    // Variabls that carries the data pulled from the line edits
    QString student_name = ui->ln_edt_stnt_nme->text();
    QString department = ui->ln_edt_stnt_dprtmnt->text();
    QString phone_number = ui->ln_edt_stnt_phn->text();
    QString email = ui->ln_edt_stnt_mail->text();
    std::string date_of_birth = ui->dateEdit->text().toStdString();
    int graduation_year= ui->cmb_grd_yr->currentText().toInt();
    int count = 0;
    int year = 0;

    for (int j=date_of_birth.size()-1;;j--){
        if (count==4)
            break;
        year += date_of_birth[j] * pow(10, count);
        count++;
    }

    bool name_is_valid, department_is_valid, phone_is_valid, email_is_valid;

    name_is_valid = valid.name_validate(student_name);
    department_is_valid = valid.department_validate(department);
    phone_is_valid = valid.phone_validate(phone_number);
    email_is_valid = valid.email_validate(email);

    // Validating the user input
    if (name_is_valid && department_is_valid && phone_is_valid && email_is_valid) {
        Student *student = new Student(student_name.toStdString(),
                                      email.toStdString(),
                                      phone_number.toStdString(),
                                      department.toStdString(),
                                      2023-year,
                                      graduation_year);

        // Insert the user into the database
        database->students.push_back(student);
        // TODO: Remove later
        auto student_data = get_student_data_as_qstrings(student);
        ui->tbl_students->setRowCount(ui->tbl_students->rowCount() + 1);
        ui->tbl_students->setItem(ui->tbl_students->rowCount()-1, 0, new QTableWidgetItem(student_data["id"]));
        ui->tbl_students->setItem(ui->tbl_students->rowCount()-1, 1, new QTableWidgetItem(student_data["name"]));
        ui->tbl_students->setItem(ui->tbl_students->rowCount()-1, 2, new QTableWidgetItem(student_data["email"]));
        ui->tbl_students->setItem(ui->tbl_students->rowCount()-1, 3, new QTableWidgetItem(student_data["department"]));
        ui->tbl_students->setItem(ui->tbl_students->rowCount()-1, 4, new QTableWidgetItem(student_data["year"]));
        qDebug()<< database->students.size();


    } else {
        // TODO: Remove later
        // TODO: Handle feedback to user
        qDebug()<< "Errorrrr";
    }

    // Reset all inputs to empty
    ui->ln_edt_stnt_nme->setText("");
    ui->ln_edt_stnt_dprtmnt->setText("");
    ui->ln_edt_stnt_phn->setText("");
    ui->ln_edt_stnt_mail->setText("");

}

// Professors



void MainWindow::on_btn_add_professor_clicked() {
    ui->ViewStack->setCurrentIndex(push_navigation(5));
}

//Display the student info
//at the selected row
void MainWindow::on_tbl_students_cellClicked(int row, int _)
{
    qDebug()<< row;
    int student_index = row;
    store_row_index(student_index);
    auto student_data = get_student_data_as_qstrings(database->students[student_index]);
    ui->stnt_code_lbl->setText("Student - " + student_data["id"]);
    ui->ln_edt_stnt_nme_2->setText(student_data["name"]);
    ui->ln_edt_stnt_dprtmnt_2->setText(student_data["department"]);
    ui->ln_edt_stnt_mail_2->setText(student_data["email"]);
    ui->ln_edt_stnt_phn_2->setText(student_data["phone"]);
    //TODO either to redefine the filed dateEdit_2 in the ui to be age or year of graduation 3chan m3ndnash attribute fl student esmha date of birth
    //Allahom bala8t
    ui->nm_lbl_stud->setText(student_data["name"]);
    ui->cmb_grd_yr_2->setCurrentText(student_data["year"]);

}

//Delete the student
//At the current row index
void MainWindow::on_pushButton_5_clicked()
{
    //row index to be deleted
    int index_to_delete = row_index_student;
    //Delete the student from the database
    database->students.erase(database->students.begin() + index_to_delete);
    qDebug()<< index_to_delete;
    qDebug()<< database->students.size();
    //Update the QTable Widget of the students
    //to display the students after modifing the database
    int tbl_students_rows_count = database->students.size();
    ui->tbl_students->setRowCount(tbl_students_rows_count);
    ui->tbl_students->verticalHeader()->setVisible(false);
    ui->tbl_students->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (auto row = 0; row < tbl_students_rows_count; row++)
    {
        auto student_data = get_student_data_as_qstrings(database->students.at(row));

        ui->tbl_students->setItem(row, 0, new QTableWidgetItem(student_data["id"]));
        ui->tbl_students->setItem(row, 1, new QTableWidgetItem(student_data["name"]));
        ui->tbl_students->setItem(row, 2, new QTableWidgetItem(student_data["email"]));
        ui->tbl_students->setItem(row, 3, new QTableWidgetItem(student_data["department"]));
        ui->tbl_students->setItem(row, 4, new QTableWidgetItem(student_data["year"]));
    }

    //Reset the Fields to default values after deleting the current student
    ui->stnt_code_lbl->setText("Student - Code");
    ui->ln_edt_stnt_nme_2->setText("Student name");
    ui->ln_edt_stnt_dprtmnt_2->setText("Department");
    ui->ln_edt_stnt_mail_2->setText("Email");
    ui->ln_edt_stnt_phn_2->setText("Phone Number");
    ui->nm_lbl_stud->setText("Student Name");
    ui->cmb_grd_yr_2->setCurrentText("Year");


}

//Edit the student and save it to the database
void MainWindow::on_pushButton_4_clicked()
{
    //Row index of the student to be saved
    int index_to_save = row_index_student;
    QString student_name = ui->ln_edt_stnt_nme_2->text();
    QString email = ui->ln_edt_stnt_mail_2->text();
    QString phone_number = ui->ln_edt_stnt_phn_2->text();
    QString department = ui->ln_edt_stnt_dprtmnt_2->text();
    int graduation_year = ui->cmb_grd_yr_2->currentText().toInt();
    int age = database->students[index_to_save]->getAge();

    // creating new student from with the edited features
    //replacing the old student with the updated version
    Student *studentNew = new Student(student_name.toStdString(),
                                   email.toStdString(),
                                   phone_number.toStdString(),
                                   department.toStdString(),
                                   age,
                                   graduation_year);
    database->students[index_to_save] = studentNew;

    // TODO refactor and make a function when called performs the following loop

    //Update the QTable Widget of the students
    //to display the students after modifing the database
    int tbl_students_rows_count = database->students.size();
    ui->tbl_students->setRowCount(tbl_students_rows_count);
    ui->tbl_students->verticalHeader()->setVisible(false);
    ui->tbl_students->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (auto row = 0; row < tbl_students_rows_count; row++)
    {
        auto student_data = get_student_data_as_qstrings(database->students.at(row));

        ui->tbl_students->setItem(row, 0, new QTableWidgetItem(student_data["id"]));
        ui->tbl_students->setItem(row, 1, new QTableWidgetItem(student_data["name"]));
        ui->tbl_students->setItem(row, 2, new QTableWidgetItem(student_data["email"]));
        ui->tbl_students->setItem(row, 3, new QTableWidgetItem(student_data["department"]));
        ui->tbl_students->setItem(row, 4, new QTableWidgetItem(student_data["year"]));
    }


}


// Admins
void MainWindow::on_btn_add_admin_clicked(){
    ui->ViewStack->setCurrentIndex(push_navigation(8));
}


void MainWindow::on_btn_add_admin_form_clicked()
{
    validate valid;

    QString admin_name = ui->ln_edt_admn_nme->text();
    QString admin_title = ui->ln_edt_admn_ttle->text();
    QString admin_phone_number = ui->ln_edt_admn_phn->text();
    QString admin_email = ui->ln_edt_admn_mail->text();
    QString admin_biography = ui->ln_edt_admn_bio->text();
    QString admin_password = ui->ln_edt_admn_pass->text();


    bool name_is_valid, title_is_valid, phone_is_valid, email_is_valid, bio_is_valid, password_is_valid;

    name_is_valid = valid.name_validate(admin_name);
    title_is_valid = valid.title_validate(admin_title);
    phone_is_valid = valid.phone_validate(admin_phone_number);
    email_is_valid = valid.email_validate(admin_email);
    bio_is_valid = valid.biography_validate(admin_biography);
    password_is_valid = valid.password_validate(admin_password);

    if (name_is_valid && title_is_valid && phone_is_valid && email_is_valid && bio_is_valid && password_is_valid) {
        Admin *admin = new Admin(admin_name.toStdString(),
                                 admin_title.toStdString(),
                                 admin_title.toStdString(),
                                 admin_email.toStdString(),
                                 admin_password.toStdString(),
                                 admin_phone_number.toStdString(),
                                 admin_biography.toStdString(),
                                 40,
                                 QDateTime::currentDateTime());


        // Insert the user into the database
       database->admins.push_back(admin);

       auto admin_data = get_admin_data_as_qstrings(admin);
       ui->tbl_admins->setRowCount(ui->tbl_admins->rowCount() + 1);
       //No ID is given ti the admin
       ui->tbl_admins->setItem(ui->tbl_admins->rowCount()-1, 0, new QTableWidgetItem(admin_data["id"]));
       ui->tbl_admins->setItem(ui->tbl_admins->rowCount()-1, 1, new QTableWidgetItem(admin_data["name"]));
       ui->tbl_admins->setItem(ui->tbl_admins->rowCount()-1, 2, new QTableWidgetItem(admin_data["title"]));
       ui->tbl_admins->setItem(ui->tbl_admins->rowCount()-1, 3, new QTableWidgetItem(admin_data["email"]));
       ui->tbl_admins->setItem(ui->tbl_admins->rowCount()-1, 4, new QTableWidgetItem(admin_data["phone"]));
       qDebug()<< database->admins.size();


}
else {
    // TODO: Remove later
    // TODO: Handle feedback to user
    qDebug()<< "Error";
}
    ui->ln_edt_admn_nme->setText("");
    ui->ln_edt_admn_ttle->setText("");
    ui->ln_edt_admn_phn->setText("");
    ui->ln_edt_admn_mail->setText("");
    ui->ln_edt_admn_bio->setText("");
    ui->ln_edt_admn_pass->setText("");
}


// Heshammmmmmmmm

void MainWindow::on_tbl_admins_cellClicked(int row, int column)
{

        qDebug()<< row;
        int admin_index = row;
        store_row_index_admin(admin_index);
        auto admin_data = get_admin_data_as_qstrings(database->admins[admin_index]);
        ui->admn_code_lbl->setText("Admin - " + admin_data["id"]);
        ui->ln_edt_admn_nme_2->setText(admin_data["name"]);
        ui->ln_edt_admn_ttle_2->setText(admin_data["title"]);
        ui->ln_edt_admn_mail_2->setText(admin_data["email"]);
        ui->ln_edt_admn_phn_2->setText(admin_data["phone"]);
        ui->ln_edt_admn_bio_2->setText(admin_data["biography"]);
        //TODO either to redefine the filed dateEdit_2 in the ui to be age or year of graduation 3chan m3ndnash attribute fl student esmha date of birth
        //Allahom bala8t
        ui->nm_lbl_admn->setText(admin_data["name"]);
    }






void MainWindow::on_pushButton_20_clicked()
{
    //row index to be deleted
    int index_to_delete = row_index_admin;
    //Delete the admin from the database
    database->admins.erase(database->admins.begin() + index_to_delete);
    qDebug()<< index_to_delete;
    qDebug()<< database->admins.size();
    //Update the QTable Widget of the admins
    //to display the admins after modifing the database
    int tbl_admins_rows_count = database->admins.size();
    ui->tbl_admins->setRowCount(tbl_admins_rows_count);
    ui->tbl_admins->verticalHeader()->setVisible(false);
    ui->tbl_admins->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (auto row = 0; row < tbl_admins_rows_count; row++)
    {
        auto admin_data = get_admin_data_as_qstrings(database->admins.at(row));

        ui->tbl_admins->setItem(row, 0, new QTableWidgetItem(admin_data["id"]));
        ui->tbl_admins->setItem(row, 1, new QTableWidgetItem(admin_data["name"]));
        ui->tbl_admins->setItem(row, 2, new QTableWidgetItem(admin_data["title"]));
        ui->tbl_admins->setItem(row, 3, new QTableWidgetItem(admin_data["email"]));
        ui->tbl_admins->setItem(row, 4, new QTableWidgetItem(admin_data["phone"]));
    }

   // Reset the Fields to default values after deleting the current admin
    ui->admn_code_lbl->setText("Admin - Code");
    ui->nm_lbl_admn->setText("Admin name");
    ui->ln_edt_admn_nme_2->setText("Admin");
    ui->ln_edt_admn_ttle_2->setText("title");
    ui->ln_edt_admn_mail_2->setText("Email");
    ui->ln_edt_admn_phn_2->setText("Phone Number");
    ui->ln_edt_admn_bio_2->setText("Admin Biography");

}


void MainWindow::on_pushButton_21_clicked()
{
    //Row index of the admin to be saved
    int index_to_save = row_index_admin;

    QString admin_name = ui->ln_edt_admn_nme_2->text();
    QString admin_title = ui->ln_edt_admn_ttle_2->text();
    QString admin_email = ui->ln_edt_admn_mail_2->text();
    QString admin_phone_number = ui->ln_edt_admn_phn_2->text();
    QString admin_biography = ui->ln_edt_admn_bio_2->text();

    // creating new admin with the updated data
    //replacing the old admin with the updated one
    Admin *adminNew = new Admin(admin_name.toStdString(),
                                admin_title.toStdString(),
                                admin_title.toStdString(),
                                admin_email.toStdString(),
                                database->admins[row_index_admin]->get_password(),
                                admin_phone_number.toStdString(),
                                admin_biography.toStdString(),
                                40,
                                QDateTime::currentDateTime());
    database->admins[index_to_save] = adminNew;

    // TODO refactor and make a function when called performs the following loop

    //Update the QTableWidget of the admins
    //to display the admins after modifing the database
    int tbl_admins_rows_count = database->admins.size();
    ui->tbl_admins->setRowCount(tbl_admins_rows_count);
    ui->tbl_admins->verticalHeader()->setVisible(false);
    ui->tbl_admins->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (auto row = 0; row < tbl_admins_rows_count; row++)
    {
        auto admin_data = get_admin_data_as_qstrings(database->admins.at(row));

        ui->tbl_admins->setItem(row, 0, new QTableWidgetItem(admin_data["id"]));
        ui->tbl_admins->setItem(row, 1, new QTableWidgetItem(admin_data["name"]));
        ui->tbl_admins->setItem(row, 2, new QTableWidgetItem(admin_data["title"]));
        ui->tbl_admins->setItem(row, 3, new QTableWidgetItem(admin_data["email"]));
        ui->tbl_admins->setItem(row, 4, new QTableWidgetItem(admin_data["phone"]));
    }


}





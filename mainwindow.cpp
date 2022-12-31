#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cmath>
#include <stack>

#include "validate.h"
#include "student.h"
#include "database.h"
#include "admin.h"
#include "professor.h"
#include "course.h"

#include "fstream"

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
Admin* login_admin;
int course_id = 0;
QTime course_time;
bool edit_course = false;
int count_student = 0;
int count_professor = 0;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//export to csv
//To be called on clicking the export button in student
void stud_export_to_csv(){
    std::ofstream os;
    os.open("studentsData.txt", std::ios::app);
    for(auto student : database->students)
    {
        os<< student->get_id() << "," << student->getName() << "," << student->getDepartment() << "," <<student->getPhone() << "," << student->getEmail()<<Qt::endl;
    }

    os.close();
}

//To be called on clicking the export button in professor
void prof_export_to_csv(){
    std::ofstream os;
    os.open("professorsData.txt", std::ios::app);
    for(auto professor : database->professors)
    {
        os<< professor->get_id() << "," << professor->getName() << "," << professor->getDepartment() << "," <<professor->getPhone() << "," << professor->getEmail()<<Qt::endl;
    }

    os.close();
}
//To be called on clicking the export button in admin
void export_to_csv(){
    std::ofstream os;
    os.open("adminsData.txt", std::ios::app);
    for(auto admin : database->admins)
    {
        os<< admin->get_id() << "," << admin->getName() << "," << admin->getDepartment() << "," <<admin->getPhone() << "," << admin->getEmail()<<Qt::endl;
    }

    os.close();
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//import csv
//import studentsData.txt
void stud_import_from_csv(){
    std::ifstream is;
    std::vector<QString> imported_students;
    is.open("adminsData.txt", std::ios::app);
    std::string Line;
    while(std::getline(is, Line))
    {
        imported_students.push_back(QString::fromStdString(Line));
        qDebug()<<"importing";
    }
    is.close();
    //TODO we created a vector carrying each line i.e each row in the form of csv
    //loop over each item in the vector and split at the comma then extract the attributes for the student and create a new student then pushit
    // to the student database mock then show the modifications on the QTableWidget
    //Do Not remove those notes for me to continue
    // Consider repeating the same for professors, admins and courses 3chan 3luka t3b
}
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


std::map<std::string, QString> get_professor_data_as_qstrings(Professor *professor) {
    std::map<std::string, QString> result;

    result["id"] = QString::fromStdString(std::to_string(professor->get_id()));
    result["name"] = QString::fromStdString(professor->getName());
    result["email"] = QString::fromStdString(professor->getEmail());
    result["department"] = QString::fromStdString(professor->getDepartment());
    result["year"]= QString::fromStdString(professor->get_graduated_from());
    result["phone"] = QString::fromStdString(professor->getPhone());
    result["Graduated From"] = QString::fromStdString(professor->get_graduated_from());
    result["PHD Subject"] = QString::fromStdString(professor->get_phd());
    result["Join"] = QString::fromStdString(professor->get_joined_on());
    result["Birth"] = QString::fromStdString(professor->get_birth());

    return result;
}


/*
std::map<QString, QDateTime> convert_String_DateTime (QString element){
    std::map<QString, QDateTime> converted;

    converted["Join_Correct"] =
}
*/

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


// TODO :
//number of students will be edited
//department will be edited
std::map<std::string, QString> get_course_data_as_qstrings (Course* course) {
    std::map<std::string, QString> result;
    result["id"] = QString::fromStdString(std::to_string(course->get_ID()));
    result["name"] = QString::fromStdString(course->get_name());
    result["department"] = QString::fromStdString(course->get_department());
    result["year"] = QString::fromStdString(std::to_string(course->get_academic_year()));
    //result["num_students"] = QString::fromStdString(std::to_string(course->get));
    result["day"] = QString::fromStdString(course->get_day());
    result["type"] = QString::fromStdString(course->get_type());
    result["hall"] = QString::fromStdString(course->get_hall());


    return result;
}




// TODO: RENAME THOSE IMMED.

//Global variable keeps track of current clicked row index in the QTableWidget
//In order to control the delete button and the save button
int row_index_student = NULL;
int row_index_admin = NULL;
int row_index_professor = NULL;
int row_index_course = NULL;



//Helper Function that takes the current clicked row index in the QTableWidget
//And passes its value to the global variable above
void store_row_index(int row){
    row_index_student = row;
}


void store_row_index_professor(int row){
    row_index_professor = row;
}

void store_row_index_admin(int row){
    row_index_admin = row;
}

void store_row_index_course(int row){
    row_index_course = row;
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

    int tbl_professors_rows_count = database->professors.size();
    ui->tbl_professors->setRowCount(tbl_professors_rows_count);
    ui->tbl_professors->verticalHeader()->setVisible(false);
    ui->tbl_professors->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (auto row = 0; row < tbl_professors_rows_count; row++)
        {
            auto prof_data = get_professor_data_as_qstrings(database->professors.at(row));

            ui->tbl_professors->setItem(row, 0, new QTableWidgetItem(prof_data["id"]));
            ui->tbl_professors->setItem(row, 1, new QTableWidgetItem(prof_data["name"]));
            ui->tbl_professors->setItem(row, 2, new QTableWidgetItem(prof_data["email"]));
            ui->tbl_professors->setItem(row, 3, new QTableWidgetItem(prof_data["department"]));
        }




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

    Admin* main_admin = new Admin("Muhamed Mustafa", "IT", "Teaching Assistant", "MuhamedMostafa@gmail.com", "123456", "01013708540","Teaching Assistant at CUFE", 27 ,QDateTime::currentDateTime());
    database->admins.push_back(main_admin);

    auto admin_data = get_admin_data_as_qstrings(main_admin);
    ui->tbl_admins->setRowCount(ui->tbl_admins->rowCount() + 1);
    ui->tbl_admins->setItem(ui->tbl_admins->rowCount()-1, 0, new QTableWidgetItem(admin_data["id"]));
    ui->tbl_admins->setItem(ui->tbl_admins->rowCount()-1, 1, new QTableWidgetItem(admin_data["name"]));
    ui->tbl_admins->setItem(ui->tbl_admins->rowCount()-1, 2, new QTableWidgetItem(admin_data["title"]));
    ui->tbl_admins->setItem(ui->tbl_admins->rowCount()-1, 3, new QTableWidgetItem(admin_data["email"]));
    ui->tbl_admins->setItem(ui->tbl_admins->rowCount()-1, 4, new QTableWidgetItem(admin_data["phone"]));
    qDebug()<< database->admins.size();





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
    Admin* admin;
    ui->btn_back->setVisible(true);
    ui->btn_logout_1->setVisible(true);
    std::string Enterd_Email = ui->lineEdit->text().toStdString();
    std::string Entered_Password = ui->lineEdit_2->text().toStdString();
    bool valid_login = false;
    for(auto i : database->admins )
    {
        if(Enterd_Email == i ->getEmail() && Entered_Password == i ->get_password())
        {
            valid_login = true;
            admin = i;
            login_admin = i;
            break;
        }
    }
    if(valid_login)
    {
        ui->ViewStack->setCurrentIndex(push_navigation(1));
        ui->label_23->setText(QString::fromStdString(admin->getName()));
        ui->label_25->setText(QString::fromStdString(admin->get_biography()));
    }
    else
    {
        // TODO: Handle feedback to user
        qDebug()<< "Errorrrr";
    }
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

void MainWindow::on_btn_nav_courses_clicked() {
    ui->ViewStack->setCurrentIndex(push_navigation(9));
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


// P4 Professors
void MainWindow::on_btn_add_professor_clicked() {
    ui->ViewStack->setCurrentIndex(push_navigation(5));
}


// P5 Add_Professors
void MainWindow::on_add_prof_form_clicked()
{
    validate valid;

    // Variabls that carries the data pulled from the line edits
    QString professor_name = ui->ln_edt_prof_nme->text();
    QString department = ui->ln_edt_prof_dprtmnt->text();
    QString phone_number = ui->ln_edt_prof_phn->text();
    QString email = ui->ln_edt_prof_mail->text();
    QString graduation_university = ui->ln_edt_prof_grd_unv->text();
    QString phd_subject = ui->ln_edt_prof_phd_sbj->text();
    QString joined_on = ui->dateEdit_join->text();
    QString date_of_birth = ui->dateEdit_birth->text();
    int graduation_year= ui->cmb_grd_yr->currentText().toInt();


 /*
    int count = 0;
    int year_birth = 0;
    int year_join = 0;


    for (int j=date_of_birth.size()-1;;j--){
        if (count==4)
            break;
        year_birth += date_of_birth[j] * pow(10, count);
        count++;
    }


    for (int i=joined_on.size()-1;;i--){
        if (count==4)
            break;
        year_join += joined_on[i] * pow(10, count);
        count++;
    }
*/




    bool name_is_valid, department_is_valid, phone_is_valid, email_is_valid, graduation_unv_is_valid, phd_subject_is_valid;
    name_is_valid = valid.name_validate(professor_name);
    department_is_valid = valid.department_validate(department);
    phone_is_valid = valid.phone_validate(phone_number);
    email_is_valid = valid.email_validate(email);
    graduation_unv_is_valid = valid.name_validate(graduation_university);
    phd_subject_is_valid = valid.name_validate(phd_subject);



    // Validating the user input
    if (name_is_valid && department_is_valid && phone_is_valid && email_is_valid && graduation_unv_is_valid && phd_subject_is_valid) {
        Professor *professor = new Professor(professor_name.toStdString(),
                                            email.toStdString(),
                                            phone_number.toStdString(),
                                            department.toStdString(),
                                            phd_subject.toStdString(),
                                            "Best Resarcher",
                                            "N/A",
                                            graduation_university.toStdString(),
                                            2023,
                                            joined_on.toStdString(),
                                            date_of_birth.toStdString());




        // Insert the user into the database
        database->professors.push_back(professor);
        // TODO: Remove later
        auto professor_data = get_professor_data_as_qstrings(professor);
        ui->tbl_professors->setRowCount(ui->tbl_professors->rowCount() + 1);
        ui->tbl_professors->setItem(ui->tbl_professors->rowCount()-1, 0, new QTableWidgetItem(professor_data["id"]));
        ui->tbl_professors->setItem(ui->tbl_professors->rowCount()-1, 1, new QTableWidgetItem(professor_data["name"]));
        ui->tbl_professors->setItem(ui->tbl_professors->rowCount()-1, 2, new QTableWidgetItem(professor_data["email"]));
        ui->tbl_professors->setItem(ui->tbl_professors->rowCount()-1, 3, new QTableWidgetItem(professor_data["department"]));
        qDebug()<< database->professors.size();


    } else {
        // TODO: Remove later
        // TODO: Handle feedback to user
        qDebug()<< "Errorrrr";
    }




        QDate date = QDate::currentDate();
        QString dateString_join = date.toString();

        QString date_string_on_db = "20/12/2015";
        QDate Date;
        Date.fromString(date_string_on_db,"dd/MM/YYYY");


    // Reset all inputs to empty
    ui->ln_edt_prof_nme->setText("");
    ui->ln_edt_prof_dprtmnt->setText("");
    ui->ln_edt_prof_phn->setText("");
    ui->ln_edt_prof_mail->setText("");
    ui->ln_edt_prof_grd_unv->setText("");
    ui->ln_edt_prof_phd_sbj->setText("");
    //ui->dateEdit_join->setDate(dateString_join);
}





//Display the Professor info
//at the selected row

void MainWindow::on_tbl_professors_cellClicked(int row, int column)
{
    qDebug()<< row;
    int prof_index = row;
    store_row_index_professor(prof_index);
    auto prof_data = get_professor_data_as_qstrings(database->professors[prof_index]);
    ui->lbl_prof_main_name->setText("Professor - " + prof_data["id"]);
    ui->ln_edt_prof_nme_2->setText(prof_data["name"]);
    ui->ln_edt_prof_dprtmnt_2->setText(prof_data["department"]);
    ui->ln_edt_prof_mail_2->setText(prof_data["email"]);
    ui->ln_edt_prof_phn_2->setText(prof_data["phone"]);
    ui->ln_edt_prof_grdf_2->setText(prof_data["Graduated From"]);
    ui->ln_edt_prof_phd_2->setText(prof_data["PHD Subject"]);
    ui->prof_code_lbl->setText(prof_data["name"]);
    ui->dateEdit_join->setDateTime(QDateTime::fromString(prof_data["join"]));
    ui->dateEdit_birth->setDateTime(QDateTime::fromString(prof_data["birth"]));
}





//Delete the student
//At the current row index
void MainWindow::on_pushButton_delete_prof_clicked()
{
    //row index to be deleted
    int index_to_delete = row_index_professor;
    //Delete the Professor from the database
    database->professors.erase(database-> professors.begin() + index_to_delete);
    qDebug()<< index_to_delete;
    qDebug()<< database-> professors.size();
    //Update the QTable Widget of the students
    //to display the students after modifing the database
    int tbl_professors_rows_count = database->professors.size();
    ui->tbl_professors->setRowCount(tbl_professors_rows_count);
    ui->tbl_professors->verticalHeader()->setVisible(false);
    ui->tbl_professors->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (auto row = 0; row < tbl_professors_rows_count; row++)
    {
        auto prof_data = get_professor_data_as_qstrings(database->professors.at(row));

        ui->tbl_professors->setItem(row, 0, new QTableWidgetItem(prof_data["id"]));
        ui->tbl_professors->setItem(row, 1, new QTableWidgetItem(prof_data["name"]));
        ui->tbl_professors->setItem(row, 2, new QTableWidgetItem(prof_data["email"]));
        ui->tbl_professors->setItem(row, 3, new QTableWidgetItem(prof_data["department"]));
        ui->tbl_professors->setItem(row, 4, new QTableWidgetItem(prof_data["year"]));
    }



    //Reset the Fields to default values after deleting the current student
    ui->lbl_prof_main_name->setText("Professor - id");
    ui->ln_edt_prof_nme_2->setText("Professor name");
    ui->ln_edt_prof_dprtmnt_2->setText("Department");
    ui->ln_edt_stnt_mail_2->setText("Email");
    ui->ln_edt_stnt_phn_2->setText("Phone Number");
    ui->ln_edt_prof_grdf_2->setText("Graduated From");
    ui->ln_edt_prof_phd_2->setText("PHD Subject");
    ui->prof_code_lbl->setText("name");







}



// *********************************************************************************** //
// *********************************************************************************** //
// *********************************************************************************** //

//Edit the Professor and save it to the database
void MainWindow::on_pushButton_prof_save_clicked()
{
    //Row index of the student to be saved
    int index_to_save = row_index_professor;

    QString professor_name = ui->ln_edt_prof_nme_2->text();
    QString department = ui->ln_edt_prof_dprtmnt_2->text();
    QString phone_number = ui->ln_edt_prof_phn_2->text();
    QString email = ui->ln_edt_prof_mail_2->text();
    QString graduation_university = ui->ln_edt_prof_grdf_2->text();
    QString phd_subject = ui->ln_edt_prof_phd_2->text();

    std::string joined_on = ui->dateEdit_join->text().toStdString();
    int year_join = 0;
    int count = 0;



    for (int i=joined_on.size()-1;;i--){
        if (count==4)
            break;
        year_join += joined_on[i] * pow(10, count);
        count++;
    }
    // creating new Professor from with the edited features
    //replacing the old student with the updated version
    Professor *professorNew = new Professor(professor_name.toStdString(),
                                        email.toStdString(),
                                        phone_number.toStdString(),
                                        department.toStdString(),
                                        phd_subject.toStdString(),
                                        "Best Resarcher",
                                        "N/A",
                                        graduation_university.toStdString(),
                                        2023-year_join,
                                        "2023",
                                        "2000");
    database->professors[index_to_save] = professorNew;


    // TODO refactor and make a function when called performs the following loop
    //Update the QTable Widget of the Professors
    //to display the Professors after modifing the database
    int tbl_professors_rows_count = database->professors.size();
    ui->tbl_professors->setRowCount(tbl_professors_rows_count);
    ui->tbl_professors->verticalHeader()->setVisible(false);
    ui->tbl_professors->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (auto row = 0; row < tbl_professors_rows_count; row++)
    {
        auto prof_data = get_professor_data_as_qstrings(database->professors.at(row));

        ui->tbl_professors->setItem(row, 0, new QTableWidgetItem(prof_data["id"]));
        ui->tbl_professors->setItem(row, 1, new QTableWidgetItem(prof_data["name"]));
        ui->tbl_professors->setItem(row, 2, new QTableWidgetItem(prof_data["email"]));
        ui->tbl_students->setItem(row, 3, new QTableWidgetItem(prof_data["department"]));
    }





}
// *********************************************************************************** //
// *********************************************************************************** //
// *********************************************************************************** //



// *********************************************************************************************************** //




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
    if(database->admins[index_to_delete]!=login_admin)
    {


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





void MainWindow::on_btn_visit_profile_clicked()
{
    Admin* admin;
    admin = login_admin;
    ui->ViewStack->setCurrentIndex(push_navigation(6)); //Go to admin profile

    ui->label_66->setText(QString::fromStdString(admin->getName()));
    ui->label_70->setText(QString::fromStdString(admin->get_title()));
    ui->label_71->setText(QString::fromStdString(admin->getPhone()));
    ui->label_74->setText(QString::fromStdString(admin->getEmail()));
    ui->label_75->setText(QString::number(admin->get_dateOfbirth()));
    ui->label_82->setText(QDateTime(admin->get_creation_date()).toString("yyyy.MM.dd" ));
    ui->label_77->setText(QString::fromStdString(admin->get_biography()));
    ui->label_67->setText(QString::fromStdString(admin->get_speciality()));
}










// TODO: clean this mess w yarab sabrni












void MainWindow::on_pushButton_3_clicked()
{   //get the name to search for from the search bar
    std::string student_name = ui->lineEdit_3->text().toStdString();
    qDebug()<<QString::fromStdString(student_name);
    bool found = 0;
    //Loop all over the students database to search for the given name
    for(auto i = 0; i<database->students.size(); i++)
    {
        if(student_name == database->students[i]->getName())
        {
            //if student is found
            qDebug()<<QString::fromStdString(database->students[i]->getName());
            int row_index = i;
            qDebug()<<"before reached";
            qDebug()<<"reached";
            found = 1;
            //reaches the matching items in the Qwidget table
            auto matching_items = ui->tbl_students->findItems(QString::fromStdString(student_name), Qt::MatchContains);
            for(auto item : matching_items)
            {
                //select the item found
                item->setSelected(true);
                //make the item clicked to display the info in the card to the left
                ui->tbl_students->cellClicked(row_index, 0);
            }

            break;
        }
    }
    // Student not found in the database
    if(!found)
    {
       //TODO Display Not student not found
        qDebug()<<"Student not found";
    }

}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QString filter_yr = ui->comboBox->currentText();
    qDebug()<<filter_yr;
    std::vector<Student*> filtered_studens;
    for(auto student : database->students)
    {
        if(QString::fromStdString(std::to_string(student->getGraduation_year())) == filter_yr)
            filtered_studens.push_back(student);
    }

    // Setting up students table
    QHeaderView* students_table_header = ui->tbl_students->horizontalHeader();
    students_table_header->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

    int tbl_students_rows_count = filtered_studens.size();
    ui->tbl_students->setRowCount(tbl_students_rows_count);
    ui->tbl_students->verticalHeader()->setVisible(false);
    ui->tbl_students->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (auto row = 0; row < tbl_students_rows_count; row++) {
        auto student_data = get_student_data_as_qstrings(filtered_studens.at(row));

        ui->tbl_students->setItem(row, 0, new QTableWidgetItem(student_data["id"]));
        ui->tbl_students->setItem(row, 1, new QTableWidgetItem(student_data["name"]));
        ui->tbl_students->setItem(row, 2, new QTableWidgetItem(student_data["email"]));
        ui->tbl_students->setItem(row, 3, new QTableWidgetItem(student_data["department"]));
        ui->tbl_students->setItem(row, 4, new QTableWidgetItem(student_data["year"]));
    }

    qDebug()<<"reached";
    qDebug()<<QString::fromStdString(std::to_string(filtered_studens.size()));
}


void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    QString department = ui->comboBox_2->currentText();
    qDebug()<<department;
    std::vector<Student*> filtered_studens;
    for(auto student : database->students)
    {
        if(QString::fromStdString(student->getDepartment()) == department)
            filtered_studens.push_back(student);
    }
    // Setting up students table
    QHeaderView* students_table_header = ui->tbl_students->horizontalHeader();
    students_table_header->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

    int tbl_students_rows_count = filtered_studens.size();
    ui->tbl_students->setRowCount(tbl_students_rows_count);
    ui->tbl_students->verticalHeader()->setVisible(false);
    ui->tbl_students->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (auto row = 0; row < tbl_students_rows_count; row++) {
        auto student_data = get_student_data_as_qstrings(filtered_studens.at(row));

        ui->tbl_students->setItem(row, 0, new QTableWidgetItem(student_data["id"]));
        ui->tbl_students->setItem(row, 1, new QTableWidgetItem(student_data["name"]));
        ui->tbl_students->setItem(row, 2, new QTableWidgetItem(student_data["email"]));
        ui->tbl_students->setItem(row, 3, new QTableWidgetItem(student_data["department"]));
        ui->tbl_students->setItem(row, 4, new QTableWidgetItem(student_data["year"]));
    }

    qDebug()<<"reached";
    qDebug()<<QString::fromStdString(std::to_string(filtered_studens.size()));

}

//courses


void MainWindow::on_btn_add_course_clicked()
{
    ui->ViewStack->setCurrentIndex(push_navigation(10));
}

// TODO :
// edit course type (enum) and category and start&end time and week day (enum)
void MainWindow::on_pushButton_15_clicked()
{
    validate valid;

    QString course_name = ui->ln_edt_stnt_nme_5->text();
    QString course_department = ui->ln_edt_stnt_nme_7->text();
    QString course_week_day = ui->cmb_grd_yr_5->currentText();
    QString course_type = ui->cmb_grd_yr_7->currentText();
    QString course_hall = ui->ln_edt_stnt_dprtmnt_5->text();
    int year = ui->cmb_grd_yr_6->currentText().toInt();

    bool name_is_valid, department_is_valid, type_is_valid, hall_is_valid;

    name_is_valid = valid.name_validate(course_name);
    department_is_valid = valid.department_validate(course_department);
    type_is_valid = valid.type_validate(course_type);
     hall_is_valid = valid.hall_validate(course_hall);


    if (name_is_valid && department_is_valid && type_is_valid  && hall_is_valid) {
        if(!edit_course) {
        Course *course = new Course(++course_id,
                                course_name.toStdString(),
                                 course_department.toStdString(),
                                 course_type.toStdString(),
                                 course_hall.toStdString(),
                                 course_week_day.toStdString(),
                                 course_time,
                                 course_time.addSecs(5400),
                                    year);

                                 database->courses.push_back(course);

        auto course_data = get_course_data_as_qstrings(course);
        ui->tbl_courses->setRowCount(ui->tbl_courses->rowCount() + 1);
        ui->tbl_courses->setItem(ui->tbl_courses->rowCount()-1, 0, new QTableWidgetItem(course_data["id"]));
        ui->tbl_courses->setItem(ui->tbl_courses->rowCount()-1, 1, new QTableWidgetItem(course_data["name"]));
        ui->tbl_courses->setItem(ui->tbl_courses->rowCount()-1, 2, new QTableWidgetItem(course_data["department"]));
        ui->tbl_courses->setItem(ui->tbl_courses->rowCount()-1, 3, new QTableWidgetItem(course_data["year"]));
        ui->tbl_courses->setItem(ui->tbl_courses->rowCount()-1, 4, new QTableWidgetItem(QString::fromStdString(std::to_string(count_student))));

 }

 else {

            Course *course = new Course(database->courses[row_index_course]->get_ID(),
                                    course_name.toStdString(),
                                     course_department.toStdString(),
                                     course_type.toStdString(),
                                     course_hall.toStdString(),
                                     course_week_day.toStdString(),
                                     course_time,
                                     course_time.addSecs(5400),
                                        year);

            database->courses[row_index_course] = course;
            ui->tbl_courses->setItem(row_index_course, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(database->courses[row_index_course]->get_ID()))));
            ui->tbl_courses->setItem(row_index_course, 1, new QTableWidgetItem(course_name));
            ui->tbl_courses->setItem(row_index_course, 2, new QTableWidgetItem(course_department));
            ui->tbl_courses->setItem(row_index_course, 3, new QTableWidgetItem(ui->cmb_grd_yr_6->currentText()));
            ui->tbl_courses->setItem(row_index_course, 4, new QTableWidgetItem(QString::fromStdString(std::to_string(count_student))));
            edit_course = false;


      }

    }
}






void MainWindow::on_pushButton_13_clicked()
{
    //get the course name to search for from the search bar
        std::string course_name = ui->lineEdit_11->text().toStdString();
        qDebug()<<QString::fromStdString(course_name);
        bool found = 0;
        //Loop all over the students database to search for the given name
        for(auto i = 0; i < database->courses.size(); i++)
        {
            if(course_name == database->courses[i]->get_name())
            {
                //if course is found
                qDebug()<<QString::fromStdString(database->courses[i]->get_name());
                int row_index = i;
                qDebug()<<"before reached";
                qDebug()<<"reached";
                found = 1;
                //searching for the matching item in the Qwidget table
                auto matching_item = ui->tbl_courses->findItems(QString::fromStdString(course_name), Qt::MatchContains);
                for(auto item : matching_item)
                {
                    //select the item found
                    item->setSelected(true);
                }

                break;
            }
        }
        //  Course not found in the database
        if(!found)
        {
           //TODO Display Not Course not found
            qDebug()<<"Course not found";
        }


}


void MainWindow::on_comboBox_7_currentIndexChanged(int index)
{
    QString filter_course_yr = ui->comboBox_7->currentText();
    qDebug()<<filter_course_yr;
    std::vector<Course*> filtered_courses;
    for(auto course : database->courses)
    {
        if(QString::fromStdString(std::to_string(course->get_academic_year())) == filter_course_yr)
            filtered_courses.push_back(course);
    }


    // Setting up courses table
    QHeaderView* courses_table_header = ui->tbl_courses->horizontalHeader();
    courses_table_header->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

    int tbl_courses_rows_count = filtered_courses.size();
    ui->tbl_courses->setRowCount(tbl_courses_rows_count);
    ui->tbl_courses->verticalHeader()->setVisible(false);
    ui->tbl_courses->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (auto row = 0; row < tbl_courses_rows_count; row++) {
        auto course_data = get_course_data_as_qstrings(filtered_courses.at(row));

        ui->tbl_courses->setItem(row, 0, new QTableWidgetItem(course_data["id"]));
        ui->tbl_courses->setItem(row, 1, new QTableWidgetItem(course_data["name"]));
        ui->tbl_courses->setItem(row, 2, new QTableWidgetItem(course_data["department"]));
        ui->tbl_courses->setItem(row, 3, new QTableWidgetItem(course_data["year"]));
        ui->tbl_courses->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(std::to_string(count_student))));
    }

    qDebug()<<"reached";
    qDebug()<<QString::fromStdString(std::to_string(filtered_courses.size()));

}


void MainWindow::on_comboBox_8_currentIndexChanged(int index)
{
    QString department = ui->comboBox_8->currentText();
    qDebug()<<department;
    std::vector<Course*> filtered_courses;
    for(auto course : database->courses)
    {
        if(QString::fromStdString(course->get_department()) == department)
            filtered_courses.push_back(course);
    }
    // Setting up courses table
    QHeaderView* course_table_header = ui->tbl_courses->horizontalHeader();
    course_table_header->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

    int tbl_courses_rows_count = filtered_courses.size();
    ui->tbl_courses->setRowCount(tbl_courses_rows_count);
    ui->tbl_courses->verticalHeader()->setVisible(false);
    ui->tbl_courses->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (auto row = 0; row < tbl_courses_rows_count; row++) {
        auto course_data = get_course_data_as_qstrings(filtered_courses.at(row));

        ui->tbl_courses->setItem(row, 0, new QTableWidgetItem(course_data["id"]));
        ui->tbl_courses->setItem(row, 1, new QTableWidgetItem(course_data["name"]));
        ui->tbl_courses->setItem(row, 2, new QTableWidgetItem(course_data["department"]));
        ui->tbl_courses->setItem(row, 3, new QTableWidgetItem(course_data["year"]));
        ui->tbl_courses->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(std::to_string(count_student))));
    }

    qDebug()<<"reached";
    qDebug()<<QString::fromStdString(std::to_string(filtered_courses.size()));

}




void MainWindow::on_comboBox_10_currentIndexChanged(int index)
{
   QString course_type = ui->comboBox_10->currentText();
   std::vector<Course*> filtered_courses;
   for(auto course : database->courses)
   {
       if((QString::fromStdString(course->get_type()) == course_type))
           filtered_courses.push_back(course);

  }
            // Setting up courses table
           QHeaderView* course_table_header = ui->tbl_courses->horizontalHeader();
           course_table_header->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

           int tbl_courses_rows_count = filtered_courses.size();
           ui->tbl_courses->setRowCount(tbl_courses_rows_count);
           ui->tbl_courses->verticalHeader()->setVisible(false);
           ui->tbl_courses->setEditTriggers(QAbstractItemView::NoEditTriggers);

           for (auto row = 0; row < tbl_courses_rows_count; row++) {
               auto course_data = get_course_data_as_qstrings(filtered_courses.at(row));

               ui->tbl_courses->setItem(row, 0, new QTableWidgetItem(course_data["id"]));
               ui->tbl_courses->setItem(row, 1, new QTableWidgetItem(course_data["name"]));
               ui->tbl_courses->setItem(row, 2, new QTableWidgetItem(course_data["department"]));
               ui->tbl_courses->setItem(row, 3, new QTableWidgetItem(course_data["year"]));
               ui->tbl_courses->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(std::to_string(count_student))));
           }

           qDebug()<<"reached";
           qDebug()<<QString::fromStdString(std::to_string(filtered_courses.size()));



}





void MainWindow::on_pushButton_19_clicked()
{
    //get the admin name to search for from the search bar
        std::string admin_name = ui->lineEdit_9->text().toStdString();
        qDebug()<<QString::fromStdString(admin_name);
        bool found = 0;
        //Loop all over the admin database to search for the given name
        for(auto i = 0; i < database->admins.size(); i++)
        {
            if(admin_name == database->admins[i]->getName())
            {
                //if admin is found
                qDebug()<<QString::fromStdString(database->admins[i]->getName());
                int row_index = i;
                qDebug()<<"before reached";
                qDebug()<<"reached";
                found = 1;
                //searching for the matching item in the Qwidget table
                auto matching_item = ui->tbl_admins->findItems(QString::fromStdString(admin_name), Qt::MatchContains);
                for(auto item : matching_item)
                {
                    //select the item found
                    item->setSelected(true);
                    //make the item clicked to display the info in the card to the left
                    ui->tbl_admins->cellClicked(row_index, 0);
                }

                break;
            }
        }
        //  Admins not found in the database
        if(!found)
        {
           //TODO Display Not Course not found
            qDebug()<<"Admin not found";
        }
}




void MainWindow::on_pushButton_9_clicked()
{
    //get the Professor name to search for from the search bar
        std::string prof_name = ui->lineEdit_4->text().toStdString();
        qDebug()<<QString::fromStdString(prof_name);
        bool found = 0;
        //Loop all over the Professors database to search for the given name
        for(auto i = 0; i < database->professors.size(); i++)
        {
            if(prof_name == database->professors[i]->getName())
            {
                //if Professor is found
                qDebug()<<QString::fromStdString(database->professors[i]->getName());
                int row_index = i;
                qDebug()<<"before reached";
                qDebug()<<"reached";
                found = 1;
                //searching for the matching item in the Qwidget table
                auto matching_item = ui->tbl_professors->findItems(QString::fromStdString(prof_name), Qt::MatchContains);
                for(auto item : matching_item)
                {
                    //select the item found
                    item->setSelected(true);
                    //make the item clicked to display the info in the card to the left
                    ui->tbl_professors->cellClicked(row_index, 0);
                }

                break;
            }
        }
        //  Professors not found in the database
        if(!found)
        {
           //TODO Display Not Professors not found
            qDebug()<<"Professor not found";
        }
}




void MainWindow::on_comboBox_4_currentIndexChanged(int index)
{
    QString filter_department = ui->comboBox_4->currentText();
    qDebug()<<filter_department;
    std::vector<Professor*> filtered_professors;
    for(auto professor : database->professors)
    {
        if(QString::fromStdString(professor->getDepartment()) == filter_department)
            filtered_professors.push_back(professor);
    }

    // Setting up professor table
    QHeaderView* professors_table_header = ui->tbl_professors->horizontalHeader();
    professors_table_header->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

    int tbl_professors_rows_count = filtered_professors.size();
    ui->tbl_professors->setRowCount(tbl_professors_rows_count);
    ui->tbl_professors->verticalHeader()->setVisible(false);
    ui->tbl_professors->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (auto row = 0; row < tbl_professors_rows_count; row++) {
        auto professor_data = get_professor_data_as_qstrings(filtered_professors.at(row));

        ui->tbl_professors->setItem(row, 0, new QTableWidgetItem(professor_data["id"]));
        ui->tbl_professors->setItem(row, 1, new QTableWidgetItem(professor_data["name"]));
        ui->tbl_professors->setItem(row, 2, new QTableWidgetItem(professor_data["email"]));
        ui->tbl_professors->setItem(row, 3, new QTableWidgetItem(professor_data["department"]));
    }

    qDebug()<<"reached";
    qDebug()<<QString::fromStdString(std::to_string(filtered_professors.size()));
}
//checks whether there is a duplicate student id
bool unique_id(std::vector<int> existance, int id)
{
    for(int x : existance)
    {
        if(x == id)
            return false;
    }
    return true;
}
//global variable keeps track of existing students in the course
std::vector<int> existance;
Student* store_current_student = nullptr;
void MainWindow::on_pushButton_18_clicked()
{
    int found = 0;
    int id = ui->ln_edt_stnt_nme_8->text().toInt();
    qDebug()<<"ID Pulled";

    for(auto student : database->students)
    {
        if(id == student->get_id() && unique_id(existance, id))
        {
            count_student++;
            store_current_student = student;
            qDebug()<<unique_id(existance, id);
            qDebug()<<"reached";
            existance.push_back(id);
            ui->tbl_students_4->setRowCount(ui->tbl_students_4->rowCount() + 1);

            QTableWidgetItem* id_item = new QTableWidgetItem(QString::fromStdString(std::to_string(student->get_id())));
            id_item->setFlags(id_item->flags() &  ~Qt::ItemIsEditable);
            ui->tbl_students_4->setItem(ui->tbl_students_4->rowCount()-1, 0, id_item);

            QTableWidgetItem* name_item = new QTableWidgetItem(QString::fromStdString(student->getName()));
            name_item->setFlags(name_item->flags() &  ~Qt::ItemIsEditable);
            ui->tbl_students_4->setItem(ui->tbl_students_4->rowCount()-1, 1, name_item);

            ui->tbl_students_4->setItem(ui->tbl_students_4->rowCount()-1, 2, new QTableWidgetItem("N/A"));

            qDebug()<<"ended";
            found  = 1;

            student->set_courses(ui->ln_edt_stnt_nme_5->text().toStdString());
            student->set_courses_grades(ui->ln_edt_stnt_nme_5->text().toStdString(),-1);
            break;

        }


    }
    if(!unique_id(existance, id))
    {
        qDebug()<<"Added student";
        //TODO display the above
    }
    else if(!found)
    {
        qDebug()<<"Not found";
        //TODO display student not found
    }
    ui->ln_edt_stnt_nme_8->clear();

}


void MainWindow::on_tbl_students_4_itemChanged(QTableWidgetItem *item)
{
    qDebug()<<"got here";
    float grade = item->text().toFloat();
    qDebug()<<grade;
    store_current_student->set_courses_grades(ui->ln_edt_stnt_nme_5->text().toStdString(),grade);

}


void MainWindow::on_timeEdit_timeChanged(const QTime &time)
{
    course_time = time;
}



void MainWindow::on_tbl_courses_cellClicked(int row, int column)
{
    edit_course = true;
    ui->ViewStack->setCurrentIndex(push_navigation(10));
    qDebug()<< row;
    int course_index = row;
    store_row_index_course(course_index);
    auto course_data = get_course_data_as_qstrings(database->courses[course_index]);
    ui->stnt_code_lbl_3->setText("course - " + course_data["id"]);
    ui->ln_edt_stnt_nme_5->setText(course_data["name"]);
    ui->ln_edt_stnt_nme_7->setText(course_data["department"]);
    ui->cmb_grd_yr_6->setCurrentText(course_data["year"]);
    ui->cmb_grd_yr_7->setCurrentText(course_data["type"]);
    ui->cmb_grd_yr_5->setCurrentText(course_data["day"]);
    ui->ln_edt_stnt_dprtmnt_5->setText(course_data["hall"]);
    ui->timeEdit->setTime(database->courses[course_index]->get_start_time());


}
//global variable keeps track of existing professor in the course
std::vector<int> existance_prof;
Professor* store_current_professor = nullptr;
void MainWindow::on_pushButton_25_clicked()
{
    int found = 0;
    int id = ui->ln_edt_prfssr_nme_9->text().toInt();
    qDebug()<<"ID Pulled";

    for(auto professor : database->professors)
    {
        if(id == professor->get_id() && unique_id(existance_prof, id))
        {
            count_professor++;
            store_current_professor = professor;
            qDebug()<<unique_id(existance_prof, id);
            qDebug()<<"reached";
            existance_prof.push_back(id);
            ui->tbl_professors_5->setRowCount(ui->tbl_professors_5->rowCount() + 1);

            QTableWidgetItem* id_item = new QTableWidgetItem(QString::fromStdString(std::to_string(professor->get_id())));
            id_item->setFlags(id_item->flags() &  ~Qt::ItemIsEditable);
            ui->tbl_professors_5->setItem(ui->tbl_professors_5->rowCount()-1, 0, id_item);

            QTableWidgetItem* name_item = new QTableWidgetItem(QString::fromStdString(professor->getName()));
            name_item->setFlags(name_item->flags() &  ~Qt::ItemIsEditable);
            ui->tbl_professors_5->setItem(ui->tbl_professors_5->rowCount()-1, 1, name_item);


            qDebug()<<"ended";
            found  = 1;
            professor->set_courses(ui->ln_edt_stnt_nme_5->text().toStdString());
            break;

        }


    }
    if(!unique_id(existance_prof, id))
    {
        qDebug()<<"Added professor";
        //TODO display the above
    }
    else if(!found)
    {
        qDebug()<<"Not found";
        //TODO display professor not found
    }
    ui->ln_edt_prfssr_nme_9->clear();

}


#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cmath>
#include <stack>

#include "validate.h"
#include "student.h"
#include "database.h"

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
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    // Initialize the database mock
    database = new Database();

    // Remove layout margin to fix the app bar to the top
    ui->ContainerView->layout()->setContentsMargins(0, 0, 0, 0);

    // Navigate to the login page on starting up
    ui->ViewStack->setCurrentIndex(push_navigation(0));

    // Hiding app bar buttons on starting up
    ui->btn_logout_1->setVisible(false);
    ui->btn_back->setVisible(false);

    // Stretching the table header
    QHeaderView* header = ui->tableWidget->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_pushButton_clicked() {
    ui->btn_back->setVisible(true);
    ui->ViewStack->setCurrentIndex(push_navigation(1));
    ui->btn_logout_1->setVisible(true);

}


void MainWindow::on_pushButton_2_clicked() {
//    ui->listWidget->addItem("test");
}

void MainWindow::on_btn_logout_1_clicked() {
    clear_navigation();
    ui->ViewStack->setCurrentIndex(0);
    ui->btn_back->setVisible(false);
    ui->btn_logout_1->setVisible(false);
}

void MainWindow::on_btn_logout_2_clicked() {
    clear_navigation();
    ui->ViewStack->setCurrentIndex(0);
    ui->btn_back->setVisible(false);
    ui->btn_logout_1->setVisible(false);
}


void MainWindow::on_btn_nav_students_clicked() {
    ui->ViewStack->setCurrentIndex(push_navigation(2));
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


void MainWindow::on_btn_add_student_clicked() {
    ui->ViewStack->setCurrentIndex(push_navigation(3));
}


void MainWindow::on_pushButton_5_clicked() {
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
        qDebug()<<database->students.size();
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


#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stack>
#include "validate.h"
#include "student.h"
#include <bits/stdc++.h>
#include <cmath>
#include "database.h"
std::stack<int> page_track;

int push_navigation(int page_number) {
    page_track.push(page_number);
    qDebug() << page_number;
    return page_number;
}

int pop_navigation() {
    page_track.pop();
    return page_track.top();;
}

void clear_navigation() {
    while (page_track.size() > 1) {
        page_track.pop();
    }
    qDebug() << page_track.top();
}
 Database *database = new Database();
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ContainerView->layout()->setContentsMargins(0, 0, 0, 0);
    ui->ViewStack->layout()->setContentsMargins(0, 0, 0, 0);
    ui->P1_Dashboard->layout()->setContentsMargins(0, 0, 0, 0);

    ui->ViewStack->setCurrentIndex(push_navigation(0));
    ui->btn_logout_1->setVisible(false);
    ui->btn_back->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->btn_back->setVisible(true);
    ui->ViewStack->setCurrentIndex(push_navigation(1));
    ui->btn_logout_1->setVisible(true);

}


void MainWindow::on_pushButton_2_clicked()
{
//    ui->listWidget->addItem("test");
}

void MainWindow::on_btn_logout_1_clicked()
{
    clear_navigation();
    ui->ViewStack->setCurrentIndex(0);
    ui->btn_back->setVisible(false);
    ui->btn_logout_1->setVisible(false);
}

void MainWindow::on_btn_logout_2_clicked()
{
    clear_navigation();
    ui->ViewStack->setCurrentIndex(0);
    ui->btn_back->setVisible(false);
    ui->btn_logout_1->setVisible(false);
}


void MainWindow::on_btn_nav_students_clicked()
{
    ui->ViewStack->setCurrentIndex(push_navigation(2));
}


void MainWindow::on_btn_back_clicked()
{
    if (page_track.top() == 0) {
        ui->btn_back->setVisible(false);
        ui->btn_logout_1->setVisible(false);
    } else {
        ui->ViewStack->setCurrentIndex(pop_navigation());
        if (page_track.top() == 0) {
            ui->btn_back->setVisible(false);
            ui->btn_logout_1->setVisible(false);
        }
    }
}


void MainWindow::on_btn_add_student_clicked()
{
    ui->ViewStack->setCurrentIndex(push_navigation(3));
}


void MainWindow::on_pushButton_5_clicked()
{
    validate valid;
    // variabls that carries the data pulled from the line edits
    QString student_name = ui->ln_edt_stnt_nme->text();
    QString department = ui->ln_edt_stnt_dprtmnt->text();
    QString phone_number = ui->ln_edt_stnt_phn->text();
    QString email = ui->ln_edt_stnt_mail->text();
    std::string date_of_birth = ui->dateEdit->text().toStdString();
    int graduation_year= ui->cmb_grd_yr->currentText().toInt();
    int count = 0;
    int year = 0;
    for(int j=date_of_birth.size()-1;;j-- )
    {
        if(count==4)
            break;
        year += date_of_birth[j] * pow(10, count);
        count++;
    }

    bool name_is_valid, department_is_valid, phone_is_valid, email_is_valid;

    name_is_valid = valid.name_validate(student_name);
    department_is_valid = valid.department_validate(department);
    phone_is_valid = valid.phone_validate(phone_number);
    email_is_valid = valid.email_validate(email);

    if(name_is_valid && department_is_valid && phone_is_valid && email_is_valid)
    {
        Student *student = new Student(student_name.toStdString(),
                                      email.toStdString(),
                                      phone_number.toStdString(),
                                      department.toStdString(),
                                      2023-year,
                                      graduation_year);


        database->students.push_back(student);
        qDebug()<<database->students.size();


    }
    else
    {
        //TODO display wrong input message
    }

    ui->ln_edt_stnt_nme->setText("");
    ui->ln_edt_stnt_dprtmnt->setText("");
    ui->ln_edt_stnt_phn->setText("");
    ui->ln_edt_stnt_mail->setText("");







}


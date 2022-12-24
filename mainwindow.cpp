#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stack>

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


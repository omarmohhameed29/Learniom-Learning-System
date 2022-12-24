#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btn_logout_1_clicked();

    void on_btn_back_clicked();

    void on_btn_login_clicked();

    void on_btn_logout_2_clicked();

    void on_btn_nav_students_clicked();

    void on_btn_add_student_clicked();

    void on_btn_add_student_form_clicked();

    void on_btn_nav_professors_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
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

    void on_btn_add_professor_clicked();

    void on_tbl_students_cellClicked(int row, int column);

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_btn_nav_admins_clicked();

    void on_btn_add_admin_clicked();

    void on_btn_add_admin_form_clicked();

   void on_tbl_admins_cellClicked(int row, int column);

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_btn_visit_profile_clicked();

    void on_pushButton_delete_prof_clicked();

    void on_pushButton_prof_save_clicked();

    void on_add_prof_form_clicked();

    void on_tbl_professors_cellClicked(int row, int column);

   // void on_pushButton_11_clicked();

    void on_btn_nav_courses_clicked();

    void on_btn_add_course_clicked();

   // void on_pushButton_9_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_13_clicked();

    void on_comboBox_7_currentIndexChanged(int index);

    void on_comboBox_8_currentIndexChanged(int index);

    void on_comboBox_10_currentIndexChanged(int index);

    void on_pushButton_15_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_9_clicked();

    void on_comboBox_4_currentIndexChanged(int index);

    void on_pushButton_18_clicked();

    void on_tbl_students_4_itemChanged(QTableWidgetItem *item);


    void on_timeEdit_timeChanged(const QTime &time);

    void on_tbl_courses_cellClicked(int row, int column);

    void on_pushButton_25_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

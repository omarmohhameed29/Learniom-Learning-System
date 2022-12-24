#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.setWindowTitle("Learniom");
    w.setMinimumWidth(1000);
    w.setMinimumHeight(729);
    w.show();

    return app.exec();
}

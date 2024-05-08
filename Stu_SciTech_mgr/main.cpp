#include "mainwindow.h"
#include <page_login.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.show();
    page_login *p =new page_login;
    p ->show();

    return a.exec();
}

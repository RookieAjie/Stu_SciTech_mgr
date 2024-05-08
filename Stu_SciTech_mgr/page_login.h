#ifndef PAGE_LOGIN_H
#define PAGE_LOGIN_H

#include <QWidget>
#include <QSqlDatabase>
#include "stu_sql.h"



namespace Ui {
class page_login;
}

class page_login : public QWidget
{
    Q_OBJECT

public:
    explicit page_login(QWidget *parent = nullptr);
    ~page_login();

    stu_sql myDatabase;
    void paintEvent(QPaintEvent *event);


private slots:
    void on_btn_login_clicked();

    void on_btn_exit_clicked();


signals:
//    void LoginSuccessfully();

private:
    Ui::page_login *ui;
};

#endif // PAGE_LOGIN_H

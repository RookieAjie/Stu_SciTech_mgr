#include "page_login.h"
#include "ui_page_login.h"
#include <QMessageBox>
#include "stumainwindow.h"
#include "mainwindow.h"
#include "qpainter.h"
#include <QPainterPath>
#include <QStyleOption>

page_login::page_login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_login)
{
    ui->setupUi(this);

    this ->update();

    ui ->stu_btn ->setChecked(true);
    ui ->manager_btn ->setChecked(false);

    this -> myDatabase.Connection();
}

page_login::~page_login()
{
    delete ui;
}

void page_login::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


void page_login::on_btn_login_clicked()
{
    QString account = ui ->le_user ->text();
    QString password = ui ->le_password ->text();
    StuMainwindow::stuAccount = account;
    qDebug() << "输入的账号：" + account;
    qDebug() << "输入的密码：" + password;

    if(ui ->stu_btn ->isChecked())//用户类型是学生
    {
        //数据库查找用户名和密码
        QSqlQuery mysql;
        mysql.prepare("select * from students where 学号 =:stu_acc");
        mysql.bindValue(":stu_acc", account);
        mysql.exec();

        QString stu_acc;
        QString stu_pass;
        while (mysql.next())
        {
            stu_acc = mysql.value("学号").toString();
            stu_pass = mysql.value("密码").toString();
        }
        //        qDebug() << "数据库账号： "+ user_acc;
        //        qDebug() << "数据库密码： "+ user_pass;

        //test
        qDebug() << stu_acc;
        mysql.clear();

        if(ui ->le_user ->text() == nullptr)
        {
            QMessageBox::warning(this, "warning!", "请输入账号！！");
            qDebug() << "未输入！！";
        }
        else if(ui ->le_password ->text() == nullptr)
        {
            QMessageBox::warning(this, "warning!", "请输入密码！！");
        }
        else if(stu_acc == account && stu_pass == password)
        {
            qDebug() << "登录成功！！";
            QMessageBox::information(this,"提示...","登陆成功！！");
            StuMainwindow * s = new StuMainwindow;
            s ->show();
            this ->~page_login();

            //            MainWindow *m = new MainWindow;
            //            m ->show();
        }
        else if(stu_acc != account )
        {
            QMessageBox::critical(this, "error!", "账号错误！请重新输入账号密码！");
            ui ->le_user ->clear();
            ui ->le_password ->clear();
            qDebug() << "登陆失败！！";
        }
        else if(stu_acc == account && stu_pass != password)
        {
            QMessageBox::critical(this, "error!", "密码错误！请重新输入密码！");
            ui ->le_password ->clear();
            qDebug() << "登陆失败！！";
        }


    }
    else if(ui ->manager_btn ->isChecked())
    {

        MainWindow::AdminAccount = account;
        QSqlQuery mysql;
        mysql.prepare("select * from admin where 账号 = :acc_num");
        mysql.bindValue(":acc_num", account);
        mysql.exec();

        QString user_acc;
        QString user_pass;
        while (mysql.next())
        {
            user_acc = mysql.value("账号").toString();
            user_pass = mysql.value("密码").toString();
        }

        //test
        mysql.clear();

        if(ui ->le_user ->text() == nullptr)
        {
            QMessageBox::warning(this, "warning!", "请输入账号！！");
            qDebug() << "未输入！！";
        }
        else if(ui ->le_password ->text() == nullptr)
        {
            QMessageBox::warning(this, "warning!", "请输入密码！！");
        }
        else if(user_acc == account && user_pass == password)
        {
            QMessageBox::information(this,"提示...","登陆成功！！");
            qDebug() << "登录成功！！";
            //emit LoginSuccessfully();
            MainWindow *m = new MainWindow;
            m ->show();
            this ->~page_login();

        }
        else if(user_acc != account )
        {
            QMessageBox::critical(this, "error!", "账号错误！请重新输入账号密码！");
            ui ->le_user ->clear();
            ui ->le_password ->clear();
            qDebug() << "登陆失败！！";
        }
        else if(user_acc == account && user_pass != password)
        {
            QMessageBox::critical(this, "error!", "密码错误！请重新输入密码！");
            ui ->le_password ->clear();
            qDebug() << "登陆失败！！";
        }
    }

}


void page_login::on_btn_exit_clicked()
{
    //退出按钮
    exit(0);
}




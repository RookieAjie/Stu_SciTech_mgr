#include "update_admin.h"
#include "ui_update_admin.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QMessageBox>

update_admin::update_admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::update_admin)
{
    ui->setupUi(this);

    if(!MainWindow::rowData.empty())
    {
        ui ->lineEdit ->setText(MainWindow::rowData.at(0));
        ui ->lineEdit_2 ->setText(MainWindow::rowData.at(1));

        ui ->lineEdit ->setEnabled(false);
    }
}

update_admin::~update_admin()
{
    delete ui;
}

void update_admin::on_pushButton_clicked()
{
    this ->close();
}


void update_admin::on_pushButton_2_clicked()
{
    QString admin_num  = ui ->lineEdit ->text();
    QString admin_pass = ui ->lineEdit_2 ->text();

    QSqlQuery mysql;

    if(admin_pass == nullptr)
    {
        QMessageBox::warning(this, "warning", "请输入要修改的管理员密码！");
    }
    else
    {
        mysql.prepare("UPDATE admin SET `密码`=:name WHERE `账号`=:num;");
        mysql.bindValue(":name", admin_pass);
        mysql.bindValue(":num", admin_num);
    }



    bool ifupdate = mysql.exec();

    if(ifupdate)
    {
        QMessageBox::information(this, "提示", "修改成功！！");
        qDebug() << "update successfully!!";
        this ->close();
    }
    else
    {
        qDebug() << "update failed!!";
    }
}


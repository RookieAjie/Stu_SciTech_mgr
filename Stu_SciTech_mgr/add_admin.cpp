#include "add_admin.h"
#include "ui_add_admin.h"
#include <QSqlQuery>
#include <QMessageBox>

add_admin::add_admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_admin)
{
    ui->setupUi(this);
}

add_admin::~add_admin()
{
    delete ui;
}

void add_admin::on_pushButton_clicked()
{
    this ->close();
}


void add_admin::on_pushButton_2_clicked()
{
    QString admin_acc  = ui ->lineEdit ->text();
    QString admin_pass = ui ->lineEdit_2 ->text();

    QSqlQuery mysql;
    if(admin_acc != nullptr && admin_pass != nullptr)
    {
        mysql.prepare("INSERT INTO admin(`账号`,`密码`) VALUE (:name, :num);");//这里！
        mysql.bindValue(":name", admin_acc);
        mysql.bindValue(":num", admin_pass);
    }
    else
    {
        QMessageBox::warning(this, "warning", "请输入管理员账户及密码！");
    }

    bool add_success = mysql.exec();
    if(add_success)
    {
        qDebug() << "add successfully!!";

        QMessageBox::information(this,"tip", "添加成功！！");
        this ->close();
    }

}


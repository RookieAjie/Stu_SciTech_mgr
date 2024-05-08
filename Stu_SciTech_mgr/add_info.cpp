#include "add_info.h"
#include "ui_add_info.h"
#include <QPushButton>
#include <QDebug>
#include <QSqlQuery>
#include "mainwindow.h"
#include <QMessageBox>

add_info::add_info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_info)
{
    ui->setupUi(this);


}

add_info::~add_info()
{
    delete ui;
}

void add_info::on_return_btn_clicked()
{
    this ->close();
}

//增添界面清空文本框内容
void add_info::on_moveall_btn_clicked()
{
    //connect(ui ->moveall_btn, &QPushButton::clicked, this, [=](){

        ui ->name_line ->clear();
        ui ->pass_line ->clear();
        ui ->keyan_line ->clear();
        ui ->age_line ->clear();
        ui ->lineEdit ->clear();

    //});
}

//添加信息
void add_info::on_addInfo_btn_clicked()
{

    QString name = ui ->name_line ->text();
    QString password = ui ->pass_line ->text();
    QString sex = ui ->comboBox->currentText();
    QString age = ui ->age_line ->text();
    QString groupID = ui ->keyan_line->text();
    QString collegeid = ui ->lineEdit->text();

    qDebug() << name;
    qDebug() << password;
    qDebug() << sex;
    qDebug() << age;

    QSqlQuery mysql;
    if(name == nullptr && password ==nullptr && age == nullptr && groupID == nullptr &&collegeid ==nullptr)
    {
        QMessageBox::warning(this, "warning", "请输入要添加的学生信息！");
    }
    else if(groupID == nullptr && sex != nullptr)
    {
        mysql.prepare("INSERT INTO Students(密码,姓名,性别,年龄,学院编号) VALUE (:pass,:nname,:ssex,:aage,:collegeID);");

        mysql.bindValue(":pass",password);
        mysql.bindValue(":nname",name);
        mysql.bindValue(":ssex",sex);
        mysql.bindValue(":aage",age);
        mysql.bindValue(":collegeID",collegeid);
    }
    else if(groupID != nullptr && sex != nullptr)
    {
        mysql.prepare("INSERT INTO Students(密码,姓名,性别,年龄,科研小组号,学院编号) VALUE (:pass,:nname,:ssex,:aage,:grpid,:collegeID);");

        mysql.bindValue(":pass",password);
        mysql.bindValue(":nname",name);
        mysql.bindValue(":ssex",sex);
        mysql.bindValue(":aage",age);
        mysql.bindValue(":grpid",groupID);
        mysql.bindValue(":collegeID",collegeid);
    }
    else if(groupID == nullptr && sex == nullptr)
    {
        mysql.prepare("INSERT INTO Students(密码,姓名,年龄,学院编号) VALUE (:pass,:nname,:aage,:collegeID);");

        mysql.bindValue(":pass",password);
        mysql.bindValue(":nname",name);
        mysql.bindValue(":aage",age);
        mysql.bindValue(":collegeID",collegeid);
    }

    bool add_success = mysql.exec();
    if(add_success)
    {
        qDebug() << "add successfully!!";
//        MainWindow m;
//        m.getInfo_Database();
        QMessageBox::information(this,"tip", "添加成功！！");
        this ->close();
    }
}


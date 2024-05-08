#include "add_college.h"
#include "ui_add_college.h"
#include <QSqlQuery>
#include <QMessageBox>

add_college::add_college(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_college)
{
    ui->setupUi(this);
}

add_college::~add_college()
{
    delete ui;
}

void add_college::on_pushButton_clicked()
{
    this ->close();
}


void add_college::on_pushButton_2_clicked()
{
        QString college_name = ui ->lineEdit_colName->text();
    QString college_intro = ui ->plainTextEdit->toPlainText();

        QSqlQuery mysql;
        if(college_name != nullptr && college_intro != nullptr)
        {
            mysql.prepare("INSERT INTO college(`学院名称`,`学院简介`) VALUE (:pass,:nname);");

            mysql.bindValue(":pass",college_name);
            mysql.bindValue(":nname",college_intro);
        }
        else
        {
            QMessageBox::warning(this, "warning", "请输入要添加的学院信息!");
        }

        bool add_success = mysql.exec();
        if(add_success)
        {
            qDebug() << "add successfully!!";
            QMessageBox::information(this,"Tip", "添加成功！！");
            this ->close();
        }

}


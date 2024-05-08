#include "add_group.h"
#include "ui_add_group.h"
#include <QSqlQuery>
#include <QMessageBox>

add_group::add_group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_group)
{
    ui->setupUi(this);
}

add_group::~add_group()
{
    delete ui;
}

void add_group::on_pushButton_clicked()
{
    this ->close();
}


void add_group::on_pushButton_2_clicked()
{
        QString group_name = ui ->name_line ->text();
        QString teacher_name = ui ->te_line ->text();
        QSqlQuery mysql;
        if(group_name == nullptr || teacher_name == nullptr)
        {
            QMessageBox::warning(this,"warning","请输入要添加的小组信息！！");
        }
        else
        {

            mysql.prepare("INSERT INTO S_Groups(小组名称,指导教师) VALUE (:name, :teacher);");

            mysql.bindValue(":name",group_name);
            mysql.bindValue(":teacher",teacher_name);
        }

        bool add_success = mysql.exec();
        if(add_success)
        {
            qDebug() << "add successfully!!";
            QMessageBox::information(this,"tip", "添加成功！！");
            this ->close();
        }
}


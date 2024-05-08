#include "add_gain.h"
#include "ui_add_gain.h"
#include <QSqlQuery>
#include <QMessageBox>

add_gain::add_gain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_gain)
{
    ui->setupUi(this);
}

add_gain::~add_gain()
{
    delete ui;
}

void add_gain::on_pushButton_clicked()
{
    this ->close();
}


void add_gain::on_pushButton_2_clicked()
{
    QString Group_id = ui ->lineEdit_GroupID ->text();
    QString Achiv_id = ui ->lineEdit_achivID ->text();

    QSqlQuery mysql;
    if(Group_id!=nullptr && Achiv_id != nullptr)
    {
        mysql.prepare("INSERT INTO Gain(科研小组组号,成果编号,审批结果) VALUE (:gid,:aid,'待审批');");

        mysql.bindValue(":gid",Group_id);
        mysql.bindValue(":aid",Achiv_id);

        bool add_success = mysql.exec();
        if(add_success)
        {
            qDebug() << "add successfully!!";

            QMessageBox::information(this,"tip", "添加成功！！");
            this ->close();
        }
    }
    else
    {
        QMessageBox::warning(this, "warning", "请输入有关信息！");
    }

}


#include "uupdate.h"
#include "ui_uupdate.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "mainwindow.h"

update::update(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::update)
{
    ui->setupUi(this);

    if(!MainWindow::rowData.empty())
    {
        ui ->lineEdit ->setText(MainWindow::rowData.at(0));
        ui ->lineEdit_2 ->setText(MainWindow::rowData.at(1));
        ui ->lineEdit_3 ->setText(MainWindow::rowData.at(2));
        ui ->lineEdit_5 ->setText(MainWindow::rowData.at(4));
        ui ->lineEdit_6 ->setText(MainWindow::rowData.at(5));
        ui ->lineEdit_7 ->setText(MainWindow::rowData.at(6));

        if(MainWindow::rowData.at(3) == "男")
        {
            ui ->comboBox ->setCurrentIndex(0);
        }
        else
        {
            ui ->comboBox ->setCurrentIndex(1);
        }

        ui ->lineEdit ->setEnabled(false);
    }

}

update::~update()
{
    delete ui;
}

void update::on_pushButton_clicked()//tag:can improve
{
    QString stu_num = ui ->lineEdit ->text();
    QString stu_nam = ui ->lineEdit_3 ->text();
    QString stu_pas = ui ->lineEdit_2 ->text();
    QString stu_sex = ui ->comboBox ->currentText();
    QString stu_age = ui ->lineEdit_5 ->text();
    QString stu_grp = ui ->lineEdit_6 ->text();
    QString stu_col = ui ->lineEdit_7 ->text();

    QSqlQuery mysql;
    if(stu_num != nullptr)
    {
        if(stu_nam != nullptr && stu_pas == nullptr && stu_sex == nullptr && stu_age == nullptr && stu_grp == nullptr &&stu_col == nullptr)
        {
            mysql.prepare("UPDATE students SET `姓名`=:name WHERE `学号`=:num;");
            mysql.bindValue(":name", stu_nam);
            mysql.bindValue(":num", stu_num);
        }
        else if(stu_nam == nullptr && stu_pas != nullptr && stu_sex == nullptr && stu_age == nullptr && stu_grp == nullptr &&stu_col == nullptr)
        {
            mysql.prepare("UPDATE students SET `密码`=:name WHERE `学号`=:num;");
            mysql.bindValue(":name", stu_pas);
            mysql.bindValue(":num", stu_num);
        }
        else if(stu_nam == nullptr && stu_pas == nullptr && stu_sex != nullptr && stu_age == nullptr && stu_grp == nullptr &&stu_col == nullptr)
        {
            mysql.prepare("UPDATE students SET `性别`=:name WHERE `学号`=:num;");
            mysql.bindValue(":name", stu_sex);
            mysql.bindValue(":num", stu_num);
        }
        else if(stu_nam == nullptr && stu_pas == nullptr && stu_sex == nullptr && stu_age != nullptr && stu_grp == nullptr &&stu_col == nullptr)
        {
            mysql.prepare("UPDATE students SET `年龄`=:name WHERE `学号`=:num;");
            mysql.bindValue(":name", stu_age);
            mysql.bindValue(":num", stu_num);
        }
        else if(stu_nam == nullptr && stu_pas == nullptr && stu_sex == nullptr && stu_age == nullptr && stu_grp != nullptr &&stu_col == nullptr)
        {
            mysql.prepare("UPDATE students SET `科研小组号`=:name WHERE `学号`=:num;");
            mysql.bindValue(":name", stu_grp);
            mysql.bindValue(":num", stu_num);

        }
        else if(stu_nam == nullptr && stu_pas == nullptr && stu_sex == nullptr && stu_age == nullptr && stu_grp == nullptr &&stu_col != nullptr)
        {
            mysql.prepare("UPDATE students SET `学院编号`=:name WHERE `学号`=:num;");
            mysql.bindValue(":name", stu_col);
            mysql.bindValue(":num", stu_num);
        }
        else if(stu_nam != nullptr && stu_pas != nullptr && stu_sex != nullptr && stu_age != nullptr && stu_grp != nullptr && stu_col != nullptr)
        {
            if(stu_grp != '0')
            {
                mysql.prepare("UPDATE students SET `姓名`=:name,`密码`=:pass,`性别`=:sex,`年龄`=:age,`科研小组号`=:grid,`学院编号`=:coll WHERE `学号`=:num;");
                mysql.bindValue(":name", stu_nam);
                mysql.bindValue(":pass", stu_pas);
                mysql.bindValue(":sex", stu_sex);
                mysql.bindValue(":age", stu_age);
                mysql.bindValue(":grid", stu_grp);
                mysql.bindValue(":coll", stu_col);
                mysql.bindValue(":num", stu_num);
            }
            else
            {
                QMessageBox::warning(this,"warning","要修改的小组编号不能不存在！");
                return;
            }
        }
        else
        {
            QMessageBox::warning(this,"warning","请输入要修改的信息！");
        }
    }
    else if(stu_num == nullptr)
    {
        QMessageBox::warning(this, "warning", "请输入要修改的学生学号！");
    }



    bool ifupdate = mysql.exec();
    if(ifupdate)
    {
        MainWindow w;
        QMessageBox::information(&w, "提示", "修改成功！！");
        this ->close();
        qDebug() << "update successfully!!";
    }
    else
    {
        qDebug() << "update failed!!";
    }
}

//清空文本框
void update::on_pushButton_3_clicked()
{
//    connect(ui ->pushButton_3, &QPushButton::clicked, this, [=](){

        ui ->lineEdit_2 ->clear();
        ui ->lineEdit_3 ->clear();
        ui ->lineEdit_5 ->clear();
        ui ->lineEdit_6 ->clear();
        ui ->lineEdit_7 ->clear();
//    });
}


void update::on_pushButton_2_clicked()
{
    this ->close();
}


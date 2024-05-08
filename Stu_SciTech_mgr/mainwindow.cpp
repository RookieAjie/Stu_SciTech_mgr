#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "achievement_add.h"
#include "achievement_update.h"
#include "uupdate.h"
#include "page_login.h"
#include "delete_stu.h"
#include "delete_achiv.h"
#include "add_info.h"
#include "add_group.h"
#include "update_group.h"
#include "delete_group.h"
#include "add_gain.h"
#include "update_gain.h"
#include "delete_gain.h"
#include "add_college.h"
#include "update_college.h"
#include "delete_college.h"
#include "add_admin.h"
#include "update_admin.h"
#include "delete_admin.h"

#include <QMessageBox>
#include <QWidget>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <QDateTime>
#include <QFileDialog>
#include <QAxObject>
#include <QMessageBox>
#include <QTextEdit>
#include <QModelIndex>
#include <QtCharts>

QString MainWindow::AdminAccount=NULL;
QStringList MainWindow::rowData;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this ->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);

    stu_sql::Connection();

    //设置表格
    this ->setInfo_table();
    this ->setInfo_table2();
    this ->setInfo_table3();
    this ->setInfo_table4();
    this ->setInfo_table5();
    this ->setInfo_table6();
    this ->setInfo_table7();
    this ->setInfo_table8();
    this ->setInfo_table9();

    QString q, qq, b, age, pp;
    QStringList a;
    QSqlQuery mysql;
    //显示管理员身份
    q = getadminName();
    ui ->label_admin->setText("[管理员："+q +",欢迎您！]");

    //查询出所有的学生人数及其平均年龄，最小年龄
    qq = getStucount();
    ui ->label_countStu->setText("--查询出"+qq+"人！--");

    a = getMinAgeStu_name();
    b = getMinAge();

    mysql.prepare("SELECT AVG(`年龄`) FROM students;");
    mysql.exec();
    mysql.next();
    age = mysql.value("AVG(`年龄`)").toString();

    for(int i = 0; i< a.size() ; i++)
    {
        pp +=  (a.at(i)+" ");
    }
    qDebug()<< pp;
    ui ->textEdit->setText("  年龄最小的学生是：“"+pp+"”，其年龄是："+b +" 岁！");
    ui ->textEdit_2->setText("平均年龄为："+age+" 岁！");
    mysql.clear();

    a.clear();
    mysql.prepare("SELECT `学院名称` FROM college;");
    mysql.exec();
    while (mysql.next()) {
        a.append(mysql.value("学院名称").toString());
    }
    qDebug()<< "a = " <<a;

    ui ->comboBox->addItems(a);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_exit_clicked()
{
    exit(0);
}

void MainWindow::setInfo_table()
{
    ui ->tableWidget ->setColumnCount(13);//列数

    //表头
    ui ->tableWidget ->setHorizontalHeaderLabels(QStringList()<< "学号" << "密码" << "姓名" << "性别"
                                                             << "年龄" << "学院名称" << "科研小组名称" << "指导教师"
                                                             <<"成果编号" << "成果名称" << "审批结果" << "获得成果时间" << "成果简介");
    //表中信息
    this ->getInfo_Database();
    //表格信息不可以被编辑
    ui ->tableWidget ->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void MainWindow::setInfo_table2()
{
    ui ->tableWidget_2 ->setColumnCount(7);//列数

    //表头
    ui ->tableWidget_2 ->setHorizontalHeaderLabels(QStringList()<< "学号" << "密码" << "姓名" << "性别" << "年龄" << "科研小组号" << "学院编号");
    //表中信息
    this ->getInfo_stu();
    //表格信息不可以被编辑
    ui ->tableWidget_2 ->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void MainWindow::setInfo_table3()
{
    ui ->tableWidget_3 ->setColumnCount(3);//列数

    //表头
    ui ->tableWidget_3 ->setHorizontalHeaderLabels(QStringList()<< "小组编号" << "小组名称" << "指导教师" );
    //表中信息
    this ->getInfo_group();
    //表格信息不可以被编辑
    ui ->tableWidget_3 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::setInfo_table4()
{
    ui ->tableWidget_4 ->setColumnCount(5);//列数

    //表头
    ui ->tableWidget_4 ->setHorizontalHeaderLabels(QStringList()<<"审批意见"<<"成果编号" << "成果名称" << "获得时间" << "简介");
    //表中信息
    this ->getInfo_achievement();
    //表格信息不可以被编辑
    ui ->tableWidget_4 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::setInfo_table5()
{
    ui ->tableWidget_5 ->setColumnCount(5);//列数

    //表头
    ui ->tableWidget_5 ->setHorizontalHeaderLabels(QStringList()<< "小组编号" << "小组名称" <<"成果编号" << "成果名称" << "审批结果" );
    //表中信息
    this ->getInfo_Gain();
    //表格信息不可以被编辑
    ui ->tableWidget_5 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::setInfo_table6()
{
    ui ->tableWidget_6 ->setColumnCount(2);//列数
    //表头
    ui ->tableWidget_6 ->setHorizontalHeaderLabels(QStringList()<< "管理员账号" << "管理员密码" );
    //表中信息
    this ->getInfo_admin();
    //表格信息不可以被编辑
    ui ->tableWidget_6 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::setInfo_table7()
{
    ui ->tableWidget_7 ->setColumnCount(3);//列数
    //表头
    ui ->tableWidget_7 ->setHorizontalHeaderLabels(QStringList()<< "学院编号" << "学院名称" << "学院简介" );
    //表中信息
    this ->getInfo_college();
    //表格信息不可以被编辑
    ui ->tableWidget_7 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::setInfo_table8()
{
    ui ->tableWidget_8 ->setColumnCount(2);//列数
    //表头
    ui ->tableWidget_8 ->setHorizontalHeaderLabels(QStringList()<< "小组编号" << "小组名称"  );
    //表中信息
    this ->getInfo_GainGroup();
    //表格信息不可以被编辑
    ui ->tableWidget_8 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::setInfo_table9()
{
    ui ->tableWidget_9 ->setColumnCount(3);//列数
    //表头
    ui ->tableWidget_9 ->setHorizontalHeaderLabels(QStringList()<< "成果号" << "成果名称" <<"审批意见" );
    //表中信息
    this ->getInfo_GainAchiv();
    //表格信息不可以被编辑
    ui ->tableWidget_9 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::getInfo_Database()
{
    QSqlQuery mysql;
    //左外连接保留空值
    mysql.prepare("select students.`学号`,students.`密码`,students.`姓名`,students.`性别`,students.`年龄`,college.`学院名称`,s_groups.`小组名称`,s_groups.`指导教师`,achievement.`成果编号`,achievement.`成果名称`,gain.`审批结果`,achievement.`时间`,achievement.`简介` "
                  "FROM students "
                  "LEFT OUTER JOIN college ON (students.`学院编号`=college.`学院编号`) "
                  "LEFT OUTER JOIN s_groups ON (students.`科研小组号`=s_groups.`小组编号`) "
                  "LEFT OUTER JOIN gain ON (s_groups.`小组编号`=gain.`科研小组组号`) "
                  "LEFT OUTER JOIN achievement ON (gain.`成果编号`=achievement.`成果编号`);");


    //连接查询
//    mysql.prepare("SELECT students.*,s_groups.`小组名称`,s_groups.`指导教师`,achievement.* "
//                  "FROM students,s_groups,gain,achievement "
//                  "WHERE students.`科研小组号`=s_groups.`小组编号` "
//                  "AND s_groups.`小组编号`=gain.`科研小组组号` "
//                  "AND gain.`成果编号`=achievement.`成果编号` "
//                  "ORDER BY students.`学号` ASC;");


    if(mysql.exec())
    {
        qDebug() << "Select success!";
    }
    else
    {
        qDebug() << "Select failed!";
    }

    int row = 0; //行数
    while (mysql.next())
    {
        ui ->tableWidget ->setRowCount(row + 1);
        ui ->tableWidget ->setItem(row, 0, new QTableWidgetItem(mysql.value("学号").toString()));
        ui ->tableWidget ->setItem(row, 1, new QTableWidgetItem(mysql.value("密码").toString()));
        ui ->tableWidget ->setItem(row, 2, new QTableWidgetItem(mysql.value("姓名").toString()));
        ui ->tableWidget ->setItem(row, 3, new QTableWidgetItem(mysql.value("性别").toString()));
        ui ->tableWidget ->setItem(row, 4, new QTableWidgetItem(mysql.value("年龄").toString()));
        ui ->tableWidget ->setItem(row, 5, new QTableWidgetItem(mysql.value("学院名称").toString()));
        ui ->tableWidget ->setItem(row, 6, new QTableWidgetItem(mysql.value("小组名称").toString()));
        ui ->tableWidget ->setItem(row, 7, new QTableWidgetItem(mysql.value("指导教师").toString()));
        ui ->tableWidget ->setItem(row, 8, new QTableWidgetItem(mysql.value("成果编号").toString()));
        ui ->tableWidget ->setItem(row, 9, new QTableWidgetItem(mysql.value("成果名称").toString()));
        ui ->tableWidget ->setItem(row, 10, new QTableWidgetItem(mysql.value("审批结果").toString()));
        ui ->tableWidget ->setItem(row, 11, new QTableWidgetItem(mysql.value("时间").toString()));
        ui ->tableWidget ->setItem(row, 12, new QTableWidgetItem(mysql.value("简介").toString()));
        row++;
    }
    ui->tableWidget->resizeColumnsToContents();
    mysql.clear();
}

void MainWindow::getInfo_stu()
{
    QSqlQuery mysql;
    //单表查询
    mysql.prepare("SELECT * "
                  "FROM students;");

    if(mysql.exec())
    {
        qDebug() << "Stu_Select success!";
    }
    else
    {
        qDebug() << "Stu_Select failed!";
    }

    int row = 0;
    while (mysql.next())
    {
        ui ->tableWidget_2 ->setRowCount(row + 1);
        ui ->tableWidget_2 ->setItem(row, 0, new QTableWidgetItem(mysql.value("学号").toString()));
        ui ->tableWidget_2 ->setItem(row, 1, new QTableWidgetItem(mysql.value("密码").toString()));
        ui ->tableWidget_2 ->setItem(row, 2, new QTableWidgetItem(mysql.value("姓名").toString()));
        ui ->tableWidget_2 ->setItem(row, 3, new QTableWidgetItem(mysql.value("性别").toString()));
        ui ->tableWidget_2 ->setItem(row, 4, new QTableWidgetItem(mysql.value("年龄").toString()));
        ui ->tableWidget_2 ->setItem(row, 5, new QTableWidgetItem(mysql.value("科研小组号").toString()));
        ui ->tableWidget_2 ->setItem(row, 6, new QTableWidgetItem(mysql.value("学院编号").toString()));
        row++;
    }
    ui->tableWidget_2->resizeColumnsToContents();
    mysql.clear();

}

void MainWindow::getInfo_group()
{
    QSqlQuery mysql;
    mysql.prepare("SELECT * "
                  "FROM s_groups;");

    if(mysql.exec())
    {
        qDebug() << "Group_Select success!";
    }
    else
    {
        qDebug() << "Group_Select failed!";
    }

    int row = 0;
    while (mysql.next())
    {
        ui ->tableWidget_3 ->setRowCount(row + 1);
        ui ->tableWidget_3 ->setItem(row, 0, new QTableWidgetItem(mysql.value("小组编号").toString()));
        ui ->tableWidget_3 ->setItem(row, 1, new QTableWidgetItem(mysql.value("小组名称").toString()));
        ui ->tableWidget_3 ->setItem(row, 2, new QTableWidgetItem(mysql.value("指导教师").toString()));
        row++;
    }
    ui->tableWidget_3->resizeColumnsToContents();
    mysql.clear();
}

void MainWindow::getInfo_achievement()
{
    QSqlQuery mysql;
    mysql.prepare("SELECT * "
                  "FROM achievement;");

    if(mysql.exec())
    {
        qDebug() << "Achievement_Select success!";
    }
    else
    {
        qDebug() << "Achievement_Select failed!";
    }

    int row = 0;
    while (mysql.next())
    {
        ui ->tableWidget_4 ->setRowCount(row + 1);
        ui ->tableWidget_4 ->setItem(row, 0, new QTableWidgetItem(mysql.value("审批意见").toString()));
        ui ->tableWidget_4 ->setItem(row, 1, new QTableWidgetItem(mysql.value("成果编号").toString()));
        ui ->tableWidget_4 ->setItem(row, 2, new QTableWidgetItem(mysql.value("成果名称").toString()));
        ui ->tableWidget_4 ->setItem(row, 3, new QTableWidgetItem(mysql.value("时间").toString()));
        ui ->tableWidget_4 ->setItem(row, 4, new QTableWidgetItem(mysql.value("简介").toString()));
        row++;
    }
    ui->tableWidget_4->resizeColumnsToContents();
    mysql.clear();
}

void MainWindow::getInfo_Gain()
{
    QSqlQuery mysql;
    mysql.prepare("SELECT s_groups.`小组编号`,s_groups.`小组名称`,achievement.`成果编号`,achievement.`成果名称`,gain.`审批结果` "
                  "FROM s_groups,gain,achievement "
                  "WHERE s_groups.`小组编号`=gain.`科研小组组号` "
                  "AND gain.`成果编号`=achievement.`成果编号`;");

    if(mysql.exec())
    {
        qDebug() << "Gain_Select success!";
    }
    else
    {
        qDebug() << "Gain_Select failed!";
    }

    int row = 0;
    while (mysql.next())
    {
        ui ->tableWidget_5 ->setRowCount(row + 1);
        ui ->tableWidget_5 ->setItem(row, 0, new QTableWidgetItem(mysql.value("小组编号").toString()));
        ui ->tableWidget_5 ->setItem(row, 1, new QTableWidgetItem(mysql.value("小组名称").toString()));
        ui ->tableWidget_5 ->setItem(row, 2, new QTableWidgetItem(mysql.value("成果编号").toString()));
        ui ->tableWidget_5 ->setItem(row, 3, new QTableWidgetItem(mysql.value("成果名称").toString()));
        ui ->tableWidget_5 ->setItem(row, 4, new QTableWidgetItem(mysql.value("审批结果").toString()));
        row++;
    }
    ui->tableWidget_5->resizeColumnsToContents();
    mysql.clear();
}

void MainWindow::getInfo_GainGroup()
{
    QSqlQuery mysql;
    mysql.prepare("SELECT * "
                  "FROM s_groups;");

    if(mysql.exec())
    {
        qDebug() << "Group_Select success!";
    }
    else
    {
        qDebug() << "Group_Select failed!";
    }

    int row = 0;
    while (mysql.next())
    {
        ui ->tableWidget_8 ->setRowCount(row + 1);
        ui ->tableWidget_8 ->setItem(row, 0, new QTableWidgetItem(mysql.value("小组编号").toString()));
        ui ->tableWidget_8 ->setItem(row, 1, new QTableWidgetItem(mysql.value("小组名称").toString()));
        //ui ->tableWidget_8 ->setItem(row, 2, new QTableWidgetItem(mysql.value("指导教师").toString()));
        row++;
    }
    ui->tableWidget_8->resizeColumnsToContents();
    mysql.clear();
}

void MainWindow::getInfo_GainAchiv()
{
    QSqlQuery mysql;
    mysql.prepare("SELECT `成果编号`,`成果名称`,`审批意见` FROM achievement WHERE achievement.`审批意见`='通过';");

    if(mysql.exec())
    {
        qDebug() << "Achievement1_Select success!";
    }
    else
    {
        qDebug() << "Achievement1_Select failed!";
    }

    int row = 0;
    while (mysql.next())
    {
        ui ->tableWidget_9 ->setRowCount(row + 1);
        ui ->tableWidget_9 ->setItem(row, 0, new QTableWidgetItem(mysql.value("成果编号").toString()));
        ui ->tableWidget_9 ->setItem(row, 1, new QTableWidgetItem(mysql.value("成果名称").toString()));
        ui ->tableWidget_9 ->setItem(row, 2, new QTableWidgetItem(mysql.value("审批意见").toString()));
        row++;
    }
    ui->tableWidget_9->resizeColumnsToContents();
    mysql.clear();
}

void MainWindow::getInfo_admin()
{
    QSqlQuery mysql;
    mysql.prepare("SELECT * FROM admin;");

    if(mysql.exec())
    {
        qDebug() << "Admin_Select success!";
    }
    else
    {
        qDebug() << "Admin_Select failed!";
    }

    int row = 0;
    while (mysql.next())
    {
        ui ->tableWidget_6 ->setRowCount(row + 1);
        ui ->tableWidget_6 ->setItem(row, 0, new QTableWidgetItem(mysql.value("账号").toString()));
        ui ->tableWidget_6 ->setItem(row, 1, new QTableWidgetItem(mysql.value("密码").toString()));
        row++;
    }
    ui->tableWidget_6->resizeColumnsToContents();
    mysql.clear();
}

void MainWindow::getInfo_college()
{
    QSqlQuery mysql;
    mysql.prepare("SELECT * FROM college;");
    if(mysql.exec())
    {
        qDebug() << "college_Select success!";
    }
    else
    {
        qDebug() << "college_Select failed!";
    }

    int row = 0;
    while (mysql.next())
    {
        ui ->tableWidget_7 ->setRowCount(row + 1);
        ui ->tableWidget_7 ->setItem(row, 0, new QTableWidgetItem(mysql.value("学院编号").toString()));
        ui ->tableWidget_7 ->setItem(row, 1, new QTableWidgetItem(mysql.value("学院名称").toString()));
        ui ->tableWidget_7 ->setItem(row, 2, new QTableWidgetItem(mysql.value("学院简介").toString()));
        row++;
    }
    ui->tableWidget_7->resizeColumnsToContents();
    mysql.clear();
}

//聚集函数count（*）统计数量
QString MainWindow::getStucount()
{
    QSqlQuery mysql;
    mysql.prepare("SELECT count(*) FROM students;");
    mysql.exec();
    mysql.next();

    qDebug() << "学生数量："+mysql.value("count(*)").toString();
    return mysql.value("count(*)").toString();
}

QString MainWindow::getGrpCount()
{
    QSqlQuery mysql;
    mysql.prepare("SELECT count(*) FROM s_groups;");
    mysql.exec();
    mysql.next();

    qDebug() << "小组数量："+mysql.value("count(*)").toString();
    return mysql.value("count(*)").toString();
}

QString MainWindow::getAchivCount()
{
    QSqlQuery mysql;
    mysql.prepare("SELECT count(*) FROM achievement;");
    mysql.exec();
    mysql.next();

    qDebug() << "成果数量："+mysql.value("count(*)").toString();
    return mysql.value("count(*)").toString();
}

QString MainWindow::getCollegeCount()
{
    QSqlQuery mysql;
    mysql.prepare("SELECT count(*) FROM college;");
    mysql.exec();
    mysql.next();

    qDebug() << "学院数量："+mysql.value("count(*)").toString();
    return mysql.value("count(*)").toString();
}

QString MainWindow::getMinAge()
{
    QSqlQuery mysql;

    //带all谓词的子查询
    mysql.prepare("SELECT students.`年龄` FROM students WHERE `年龄`<= ALL (SELECT `年龄` FROM students);");
    mysql.exec();
    mysql.next();

    qDebug() << "年纪最小的是："+mysql.value("年龄").toString();
    return mysql.value("年龄").toString();
}
QStringList MainWindow::getMinAgeStu_name()
{
    QSqlQuery mysql;
    QStringList name;
    //带all谓词的子查询
    mysql.prepare("SELECT students.`姓名` FROM students WHERE `年龄`<= ALL (SELECT `年龄` FROM students);");
    mysql.exec();
    while (mysql.next())
    {
        qDebug() << " 其姓名是："+mysql.value("姓名").toString();
        name.append(mysql.value("姓名").toString());
    };
    qDebug() << name;

    return name;
}

QString MainWindow::getadminName()
{
    QSqlQuery mysql;
    mysql.prepare("SELECT * FROM admin WHERE `账号`=:number;");
    mysql.bindValue(":number",MainWindow::AdminAccount);
    mysql.exec();
    mysql.next();
    return mysql.value("账号").toString();
}


void MainWindow::on_add_btn_clicked()
{
    add_info *a = new add_info;
    a ->show();
}


void MainWindow::on_search_btn_clicked()
{
    QString q;
    QSqlQuery mysql;
    QString name = ui ->lineEdit_sql->text();
    QString college = ui->comboBox->currentText();

    if(!name.isEmpty())
    {
        if(college == "全部学院")
        {
            //使用like关键字的模糊查询
            mysql.prepare("SELECT students.`学号`,students.`密码`,students.`姓名`,students.`性别`,students.`年龄`,college.`学院名称`,s_groups.`小组名称`,s_groups.`指导教师`,achievement.`成果编号`,achievement.`成果名称`,gain.`审批结果`,achievement.`时间`,achievement.`简介` FROM students LEFT OUTER JOIN college ON (students.`学院编号`=college.`学院编号`) LEFT OUTER JOIN s_groups ON (students.`科研小组号`=s_groups.`小组编号`) LEFT OUTER JOIN gain ON (s_groups.`小组编号`=gain.`科研小组组号`) LEFT OUTER JOIN achievement ON (gain.`成果编号`=achievement.`成果编号`) WHERE `姓名` LIKE :name;");

            //%的占位符问题解决
            mysql.bindValue(":name",QString("%%1%").arg(name));

            if(mysql.exec())
            {
                qDebug() << "模糊姓名查询全部学院成功!";
            }
            else
            {
                qDebug() << "模糊姓名查询全部学院失败!";
            }
            ui ->tableWidget ->clearContents();
            ui->tableWidget->setRowCount(0);

            int row = 0;
            while (mysql.next())
            {
                ui ->tableWidget ->setRowCount(row + 1);
                ui ->tableWidget ->setItem(row, 0, new QTableWidgetItem(mysql.value("学号").toString()));
                ui ->tableWidget ->setItem(row, 1, new QTableWidgetItem(mysql.value("密码").toString()));
                ui ->tableWidget ->setItem(row, 2, new QTableWidgetItem(mysql.value("姓名").toString()));
                ui ->tableWidget ->setItem(row, 3, new QTableWidgetItem(mysql.value("性别").toString()));
                ui ->tableWidget ->setItem(row, 4, new QTableWidgetItem(mysql.value("年龄").toString()));
                ui ->tableWidget ->setItem(row, 5, new QTableWidgetItem(mysql.value("学院名称").toString()));
                ui ->tableWidget ->setItem(row, 6, new QTableWidgetItem(mysql.value("小组名称").toString()));
                ui ->tableWidget ->setItem(row, 7, new QTableWidgetItem(mysql.value("指导教师").toString()));
                ui ->tableWidget ->setItem(row, 8, new QTableWidgetItem(mysql.value("成果编号").toString()));
                ui ->tableWidget ->setItem(row, 9, new QTableWidgetItem(mysql.value("成果名称").toString()));
                ui ->tableWidget ->setItem(row, 10, new QTableWidgetItem(mysql.value("审批结果").toString()));
                ui ->tableWidget ->setItem(row, 11, new QTableWidgetItem(mysql.value("时间").toString()));
                ui ->tableWidget ->setItem(row, 12, new QTableWidgetItem(mysql.value("简介").toString()));
                row++;
            }
            q = QString::number(row, 10);
            ui->tableWidget->resizeColumnsToContents();
            mysql.clear();
        }
        else
        {
            //使用like关键字的模糊查询
            mysql.prepare("SELECT students.`学号`,students.`密码`,students.`姓名`,students.`性别`,students.`年龄`,college.`学院名称`,s_groups.`小组名称`,s_groups.`指导教师`,achievement.`成果编号`,achievement.`成果名称`,gain.`审批结果`,achievement.`时间`,achievement.`简介` FROM students LEFT OUTER JOIN college ON (students.`学院编号`=college.`学院编号`) LEFT OUTER JOIN s_groups ON (students.`科研小组号`=s_groups.`小组编号`) LEFT OUTER JOIN gain ON (s_groups.`小组编号`=gain.`科研小组组号`) LEFT OUTER JOIN achievement ON (gain.`成果编号`=achievement.`成果编号`) WHERE `姓名` LIKE :name AND `学院名称`=:col_name;");

            //%的占位符问题解决
            mysql.bindValue(":name",QString("%%1%").arg(name));
            mysql.bindValue(":col_name",college);

            if(mysql.exec())
            {
                qDebug() << "模糊姓名查询特定学院成功!";
            }
            else
            {
                qDebug() << "模糊姓名查询特定学院失败!";
            }
            ui ->tableWidget ->clearContents();
            ui->tableWidget->setRowCount(0);

            int row = 0;
            while (mysql.next())
            {
                ui ->tableWidget ->setRowCount(row + 1);
                ui ->tableWidget ->setItem(row, 0, new QTableWidgetItem(mysql.value("学号").toString()));
                ui ->tableWidget ->setItem(row, 1, new QTableWidgetItem(mysql.value("密码").toString()));
                ui ->tableWidget ->setItem(row, 2, new QTableWidgetItem(mysql.value("姓名").toString()));
                ui ->tableWidget ->setItem(row, 3, new QTableWidgetItem(mysql.value("性别").toString()));
                ui ->tableWidget ->setItem(row, 4, new QTableWidgetItem(mysql.value("年龄").toString()));
                ui ->tableWidget ->setItem(row, 5, new QTableWidgetItem(mysql.value("学院名称").toString()));
                ui ->tableWidget ->setItem(row, 6, new QTableWidgetItem(mysql.value("小组名称").toString()));
                ui ->tableWidget ->setItem(row, 7, new QTableWidgetItem(mysql.value("指导教师").toString()));
                ui ->tableWidget ->setItem(row, 8, new QTableWidgetItem(mysql.value("成果编号").toString()));
                ui ->tableWidget ->setItem(row, 9, new QTableWidgetItem(mysql.value("成果名称").toString()));
                ui ->tableWidget ->setItem(row, 10, new QTableWidgetItem(mysql.value("审批结果").toString()));
                ui ->tableWidget ->setItem(row, 11, new QTableWidgetItem(mysql.value("时间").toString()));
                ui ->tableWidget ->setItem(row, 12, new QTableWidgetItem(mysql.value("简介").toString()));
                row++;
            }
            q = QString::number(row, 10);
            ui->tableWidget->resizeColumnsToContents();
            mysql.clear();
        }
    }
    else if(name.isEmpty())
    {
        if(college == "全部学院")
        {
            ui ->tableWidget ->clearContents();
            this ->getInfo_Database();
            q = getStucount();
        }
        else
        {
            //使用like关键字的模糊查询
            mysql.prepare("SELECT students.`学号`,students.`密码`,students.`姓名`,students.`性别`,students.`年龄`,college.`学院名称`,s_groups.`小组名称`,s_groups.`指导教师`,achievement.`成果编号`,achievement.`成果名称`,gain.`审批结果`,achievement.`时间`,achievement.`简介` FROM students LEFT OUTER JOIN college ON (students.`学院编号`=college.`学院编号`) LEFT OUTER JOIN s_groups ON (students.`科研小组号`=s_groups.`小组编号`) LEFT OUTER JOIN gain ON (s_groups.`小组编号`=gain.`科研小组组号`) LEFT OUTER JOIN achievement ON (gain.`成果编号`=achievement.`成果编号`) WHERE `学院名称`=:col_name;");

            //%的占位符问题解决
            mysql.bindValue(":col_name",college);

            if(mysql.exec())
            {
                qDebug() << "查询特定学院成功!";
            }
            else
            {
                qDebug() << "查询特定学院失败!";
            }
            ui ->tableWidget ->clearContents();
            ui->tableWidget->setRowCount(0);

            int row = 0;
            while (mysql.next())
            {
                ui ->tableWidget ->setRowCount(row + 1);
                ui ->tableWidget ->setItem(row, 0, new QTableWidgetItem(mysql.value("学号").toString()));
                ui ->tableWidget ->setItem(row, 1, new QTableWidgetItem(mysql.value("密码").toString()));
                ui ->tableWidget ->setItem(row, 2, new QTableWidgetItem(mysql.value("姓名").toString()));
                ui ->tableWidget ->setItem(row, 3, new QTableWidgetItem(mysql.value("性别").toString()));
                ui ->tableWidget ->setItem(row, 4, new QTableWidgetItem(mysql.value("年龄").toString()));
                ui ->tableWidget ->setItem(row, 5, new QTableWidgetItem(mysql.value("学院名称").toString()));
                ui ->tableWidget ->setItem(row, 6, new QTableWidgetItem(mysql.value("小组名称").toString()));
                ui ->tableWidget ->setItem(row, 7, new QTableWidgetItem(mysql.value("指导教师").toString()));
                ui ->tableWidget ->setItem(row, 8, new QTableWidgetItem(mysql.value("成果编号").toString()));
                ui ->tableWidget ->setItem(row, 9, new QTableWidgetItem(mysql.value("成果名称").toString()));
                ui ->tableWidget ->setItem(row, 10, new QTableWidgetItem(mysql.value("审批结果").toString()));
                ui ->tableWidget ->setItem(row, 11, new QTableWidgetItem(mysql.value("时间").toString()));
                ui ->tableWidget ->setItem(row, 12, new QTableWidgetItem(mysql.value("简介").toString()));
                row++;
            }
            q = QString::number(row, 10);
            ui->tableWidget->resizeColumnsToContents();
            mysql.clear();
        }
    }
    ui ->label_6->setText("--共 "+q+" 条数据！--");
    QMessageBox::information(this, "Tip", "查询成功！");
}


void MainWindow::on_pushButton_clicked()
{
    QString name = ui ->lineEdit_StuMOHU->text();
    if(name != nullptr)
    {
        QSqlQuery mysql;
        //使用like关键字的模糊查询
        mysql.prepare("SELECT * FROM students WHERE `姓名` LIKE :name;");

        //%的占位符问题解决
        mysql.bindValue(":name",QString("%%1%").arg(name));

        if(mysql.exec())
        {
            qDebug() << "模糊_Stu_Select success!";
        }
        else
        {
            qDebug() << "模糊_Stu_Select failed!";
        }
        ui ->tableWidget_2 ->clearContents();

        int row = 0;
        while (mysql.next())
        {
            //qDebug() << mysql.value("姓名").toString();
            ui ->tableWidget_2 ->setRowCount(row + 1);
            ui ->tableWidget_2 ->setItem(row, 0, new QTableWidgetItem(mysql.value("学号").toString()));
            ui ->tableWidget_2 ->setItem(row, 1, new QTableWidgetItem(mysql.value("密码").toString()));
            ui ->tableWidget_2 ->setItem(row, 2, new QTableWidgetItem(mysql.value("姓名").toString()));
            ui ->tableWidget_2 ->setItem(row, 3, new QTableWidgetItem(mysql.value("性别").toString()));
            ui ->tableWidget_2 ->setItem(row, 4, new QTableWidgetItem(mysql.value("年龄").toString()));
            ui ->tableWidget_2 ->setItem(row, 5, new QTableWidgetItem(mysql.value("科研小组号").toString()));
            ui ->tableWidget_2 ->setItem(row, 6, new QTableWidgetItem(mysql.value("学院编号").toString()));
            row++;
        }

        ui->tableWidget_2->resizeColumnsToContents();
        mysql.clear();
    }
    else
    {
        ui ->tableWidget_2 ->clearContents();
        this ->getInfo_stu();
    }

    QMessageBox::information(this, "Tip", "查询成功！");
}

//学生表删除
void MainWindow::on_delete_btn_clicked()
{
    MainWindow::rowData.clear();
    int currentRowIndex = ui ->tableWidget_2 ->currentRow();
    if(currentRowIndex > -1)
    {
        for(int i=0; i< ui ->tableWidget_2->columnCount();i++)
        {
        QTableWidgetItem *item=ui->tableWidget_2->item(currentRowIndex,i);
        MainWindow::rowData.append(item ->text());
        }
        qDebug() << MainWindow::rowData;
        delete_Stu *d = new delete_Stu;
        d ->show();
    }
    else
    {
        QMessageBox::warning(this, "warning", "请选择要删除的学生！");
    }

//    QString stu_num = ui ->lineEdit_num ->text();
//    QSqlQuery mysql;
//    mysql.prepare("DELETE FROM students WHERE `学号` = :number");
//    mysql.bindValue(":number", stu_num);
//    bool ifdel = mysql.exec();
//    ui ->lineEdit_num ->clear();
//    if(ifdel)
//    {
//        QMessageBox::information(this, "提示", "删除成功！！");
//        qDebug() << "delete successfully!!";
//    }
//    else
//    {
//        qDebug() << "delete failed!!";
//    }
}


void MainWindow::on_update_btn_clicked()
{
    MainWindow::rowData.clear();
    int currentRowIndex = ui ->tableWidget_2 ->currentRow();
    if(currentRowIndex > -1)
    {
        for(int i=0; i< ui ->tableWidget_2->columnCount();i++)
        {
        QTableWidgetItem *item=ui->tableWidget_2->item(currentRowIndex,i);
        MainWindow::rowData.append(item ->text());
        }
        qDebug() << MainWindow::rowData;
        class update *u = new class update();
        u ->show();
    }
    else
    {
        QMessageBox::warning(this, "warning", "请选择要修改的学生信息！");
    }

}


void MainWindow::on_pushButton_2_clicked()
{
    QString q;
    QString name = ui ->lineEdit->text();
    if(name != nullptr)
    {
        QSqlQuery mysql;
        //使用like关键字的模糊查询
        mysql.prepare("SELECT * FROM s_groups WHERE `小组名称` LIKE :name;");

        //%的占位符问题解决
        mysql.bindValue(":name",QString("%%1%").arg(name));

        if(mysql.exec())
        {
            qDebug() << "模糊_Stu_Select success!";
        }
        else
        {
            qDebug() << "模糊_Stu_Select failed!";
        }
        ui ->tableWidget_3 ->clearContents();

        int row = 0;
        while (mysql.next())
        {
            ui ->tableWidget_3 ->setRowCount(row + 1);
            ui ->tableWidget_3 ->setItem(row, 0, new QTableWidgetItem(mysql.value("小组编号").toString()));
            ui ->tableWidget_3 ->setItem(row, 1, new QTableWidgetItem(mysql.value("小组名称").toString()));
            ui ->tableWidget_3 ->setItem(row, 2, new QTableWidgetItem(mysql.value("指导教师").toString()));
            row++;
        }
        q = QString::number(row, 10);
        ui->tableWidget_3->resizeColumnsToContents();
        mysql.clear();
    }
    else
    {
        ui ->tableWidget_3 ->clearContents();
        this ->getInfo_group();
        q = getGrpCount();
    }
    ui ->label_GrpCount->setText("共"+q+"组！");
    QMessageBox::information(this, "Tip", "查询成功！");

}


void MainWindow::on_addgroup_btn_clicked()
{
    add_group *a = new add_group;
    a ->show();
}

//组删除
void MainWindow::on_delGroup_btn_clicked()
{
    MainWindow::rowData.clear();
    int currentRowIndex = ui ->tableWidget_3 ->currentRow();
    if(currentRowIndex > -1)
    {
        for(int i=0; i< ui ->tableWidget_3->columnCount();i++)
        {
        QTableWidgetItem *item=ui->tableWidget_3->item(currentRowIndex,i);
        MainWindow::rowData.append(item ->text());
        }
        qDebug() << MainWindow::rowData;
        delete_group *d = new delete_group;
        d ->show();
    }
    else
    {
        QMessageBox::warning(this, "warning", "请选择要删除的小组！");
    }
}

//小组表修改
void MainWindow::on_updategroup_btn_clicked()
{
    MainWindow::rowData.clear();
    int currentRowIndex = ui ->tableWidget_3 ->currentRow();
    if(currentRowIndex > -1)
    {
        for(int i=0; i< ui ->tableWidget_3->columnCount();i++)
        {
        QTableWidgetItem *item=ui->tableWidget_3->item(currentRowIndex,i);
        MainWindow::rowData.append(item ->text());
        }
        qDebug() << MainWindow::rowData;
        update_group *u = new update_group;
        u ->show();
    }
    else
    {
        QMessageBox::warning(this, "warning", "请选择要修改的小组信息！");
    }
}


void MainWindow::on_achivSearch_btn_clicked()
{
    QString q;
    QString name = ui ->lineEdit_achi->text();
    if(name != nullptr)
    {
        QSqlQuery mysql;
        //使用like关键字的模糊查询
        mysql.prepare("SELECT * FROM achievement WHERE `成果名称` LIKE :name;");

        //%的占位符问题解决
        mysql.bindValue(":name",QString("%%1%").arg(name));

        if(mysql.exec())
        {
            qDebug() << "模糊_Stu_Select success!";
        }
        else
        {
            qDebug() << "模糊_Stu_Select failed!";
        }
        ui ->tableWidget_4 ->clearContents();

        int row = 0;
        while (mysql.next())
        {
            ui ->tableWidget_4 ->setRowCount(row + 1);
            ui ->tableWidget_4 ->setItem(row, 0, new QTableWidgetItem(mysql.value("审批意见").toString()));
            ui ->tableWidget_4 ->setItem(row, 1, new QTableWidgetItem(mysql.value("成果编号").toString()));
            ui ->tableWidget_4 ->setItem(row, 2, new QTableWidgetItem(mysql.value("成果名称").toString()));
            ui ->tableWidget_4 ->setItem(row, 3, new QTableWidgetItem(mysql.value("时间").toString()));
            ui ->tableWidget_4 ->setItem(row, 4, new QTableWidgetItem(mysql.value("简介").toString()));
            row++;
        }
        q = QString::number(row, 10);
        ui->tableWidget_4->resizeColumnsToContents();
        mysql.clear();
    }
    else
    {
        ui ->tableWidget_4 ->clearContents();
        this ->getInfo_achievement();
        q = getAchivCount();
    }
    ui ->label_achivCount->setText("共 "+q+" 个成果！");
    QMessageBox::information(this, "Tip", "查询成功！");

}

void MainWindow::on_Addachiv_btn_2_clicked()
{
    achievement_add *a = new achievement_add;
    a ->show();
}

//成果表修改
void MainWindow::on_updateAchiv_btn_clicked()
{
    MainWindow::rowData.clear();
    int currentRowIndex = ui ->tableWidget_4 ->currentRow();
    if(currentRowIndex > -1)
    {
        for(int i=0; i< ui ->tableWidget_4->columnCount();i++)
        {
            QTableWidgetItem *item=ui->tableWidget_4->item(currentRowIndex,i);
            MainWindow::rowData.append(item ->text());
        }
        qDebug() << MainWindow::rowData;
        achievement_update *ac =new achievement_update;
        ac ->show();
    }
    else
    {
        QMessageBox::warning(this, "warning", "请选择要修改的成果信息！");
    }
}

//成果信息删除
void MainWindow::on_del_btn_clicked()
{

    MainWindow::rowData.clear();
    int currentRowIndex = ui ->tableWidget_4 ->currentRow();
    if(currentRowIndex > -1)
    {
        for(int i=0; i< ui ->tableWidget_4->columnCount();i++)
        {
            QTableWidgetItem *item=ui->tableWidget_4->item(currentRowIndex,i);
            MainWindow::rowData.append(item ->text());
        }
        qDebug() << MainWindow::rowData;
        delete_achiv *d = new delete_achiv;
        d ->show();
    }
    else
    {
        QMessageBox::warning(this, "warning", "请选择要删除的成果！");
    }
//    QString achi_num = ui ->achiNum_del ->text();
//    QSqlQuery mysql;
//    QSqlQuery mysql2;
//    mysql2.prepare("DELETE FROM gain WHERE `成果编号` = :numbe");
//    mysql2.bindValue(":numbe", achi_num);
//    mysql.prepare("DELETE FROM achievement WHERE `成果编号` = :number");
//    mysql.bindValue(":number", achi_num);
//    mysql2.exec();
//    bool ifdel = mysql.exec();
//    ui ->achiNum_del ->clear();
//    if(ifdel)
//    {
//        QMessageBox::information(this, "提示", "删除成功！！");
//        qDebug() << "delete successfully!!";
//    }
//    else
//    {
//        qDebug() << "delete failed!!";
//    }
}


void MainWindow::on_SearchForGain_btn_clicked()
{
    this ->getInfo_Gain();
    this ->getInfo_GainGroup();
    this ->getInfo_GainAchiv();
    QMessageBox::information(this, "Tip", "查询成功！");
}


void MainWindow::on_addGain_btn_clicked()
{
    add_gain *a = new add_gain;
    a ->show();
}


void MainWindow::on_GainUpdate_btn_clicked()
{
    MainWindow::rowData.clear();
    int currentRowIndex = ui ->tableWidget_5 ->currentRow();
    if(currentRowIndex > -1)
    {
        for(int i=0; i< ui ->tableWidget_5->columnCount();i++)
        {
            QTableWidgetItem *item=ui->tableWidget_5->item(currentRowIndex,i);
            MainWindow::rowData.append(item ->text());
        }
        qDebug() << MainWindow::rowData;
        update_gain *up = new update_gain;
        up ->show();
    }
    else
    {
        QMessageBox::warning(this, "warning", "请在左侧显示框中选择要修改的小组！");
    }
}


void MainWindow::on_delet_btn_clicked()
{

    MainWindow::rowData.clear();
    int currentRowIndex = ui ->tableWidget_5 ->currentRow();
    if(currentRowIndex > -1)
    {
        for(int i=0; i< ui ->tableWidget_5->columnCount();i++)
        {
            QTableWidgetItem *item=ui->tableWidget_5->item(currentRowIndex,i);
            MainWindow::rowData.append(item ->text());
        }
        qDebug() << MainWindow::rowData;
        delete_gain *d = new delete_gain;
        d ->show();
    }
    else
    {
        QMessageBox::warning(this, "warning", "请在左侧显示框选择要删除的信息！");
    }
}


void MainWindow::on_search_btn_2_clicked()
{
    this ->getInfo_admin();
    QMessageBox::information(this, "Tip", "查询成功！");
}


void MainWindow::on_add_btn_2_clicked()
{
    add_admin *a = new add_admin;
    a ->show();
}


void MainWindow::on_change_btn_clicked()
{
    MainWindow::rowData.clear();
    int currentRowIndex = ui ->tableWidget_6 ->currentRow();
    if(currentRowIndex > -1)
    {
        for(int i=0; i< ui ->tableWidget_6->columnCount();i++)
        {
            QTableWidgetItem *item=ui->tableWidget_6->item(currentRowIndex,i);
            MainWindow::rowData.append(item ->text());
        }
        qDebug() << MainWindow::rowData;
        update_admin *a = new update_admin;
        a ->show();
    }
    else
    {
        QMessageBox::warning(this, "warning", "请在显示框中选择要修改的管理员！");
    }
}


void MainWindow::on_del_btn_2_clicked()
{
    MainWindow::rowData.clear();
    int currentRowIndex = ui ->tableWidget_6 ->currentRow();
    if(currentRowIndex > -1)
    {
        for(int i=0; i< ui ->tableWidget_6->columnCount();i++)
        {
            QTableWidgetItem *item=ui->tableWidget_6->item(currentRowIndex,i);
            MainWindow::rowData.append(item ->text());
        }
        qDebug() << MainWindow::rowData;
        delete_admin *a = new delete_admin;
        a ->show();
    }
    else
    {
        QMessageBox::warning(this, "warning", "请在显示框中选择要删除的管理员！");
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    page_login *p = new page_login;
    p ->show();
    this ->close();
}




void MainWindow::on_pushButton_4_clicked()
{
    QString q;
    QString name = ui ->lineEdit_StuMOHU->text();
    if(name != nullptr)
    {
        QSqlQuery mysql;
        //使用like关键字的模糊查询
        mysql.prepare("SELECT * FROM students WHERE `姓名` LIKE :name;");

        //%的占位符问题解决
        mysql.bindValue(":name",QString("%%1%").arg(name));

        mysql.exec();

        int row = 0;
        while (mysql.next())
        {

            row++;
        }
        q = QString::number(row, 10);
        mysql.clear();
    }
    else
    {
        q = getStucount();
    }

    ui ->label_countStu->setText("--查询出"+q+"人！--");
    QMessageBox::information(this, "Tip", "统计成功！");
}

//查询年纪最小的学生
void MainWindow::on_pushButton_5_clicked()
{
    QString name = ui ->lineEdit_StuMOHU->text();
    QStringList q;//年纪最小的可能不止一个人
    QString p;//年纪最小学生的年纪
    QString pp;
    QSqlQuery mysql;
    QSqlQuery mmysql;
    QSqlQuery mmmysql;
    QString age;

    if(name == nullptr)//所有学生
    {
        q = getMinAgeStu_name();
        p = getMinAge();

        //带all谓词的子查询
        mysql.prepare("SELECT AVG(`年龄`) FROM students;");
        mysql.exec();
        mysql.next();
        age = mysql.value("AVG(`年龄`)").toString();
    }
    else//模糊查询出的学生
    {
        //最小年纪学生姓名
        //带all谓词的子查询
        mysql.prepare("SELECT students.`姓名` FROM students WHERE `年龄`<= ALL (SELECT `年龄` FROM students WHERE `姓名` LIKE :na) AND `姓名` LIKE :na;");
        mysql.bindValue(":na",QString("%%1%").arg(name));
        mysql.exec();
        while (mysql.next())
        {
            qDebug() << " 其姓名是："+mysql.value("姓名").toString();
            q.append(mysql.value("姓名").toString());
        };

        //最小年纪学生年纪
        //带all谓词的子查询
        mmysql.prepare("SELECT students.`年龄` FROM students WHERE `年龄`<= ALL (SELECT `年龄` FROM students WHERE `姓名` LIKE :na) AND `姓名` LIKE :na;");
        mmysql.bindValue(":na",QString("%%1%").arg(name));
        mmysql.exec();
        mmysql.next();
        qDebug() << "年纪最小的是："+mmysql.value("年龄").toString();
        p = mmysql.value("年龄").toString();

        //平均年纪
        mmmysql.prepare("SELECT AVG(`年龄`) FROM students WHERE  `姓名` LIKE :na;");
        mmmysql.bindValue(":na",QString("%%1%").arg(name));
        mmmysql.exec();
        mmmysql.next();
        age = mmmysql.value("AVG(`年龄`)").toString();

    }

    for(int i = 0; i< q.size() ; i++)
    {
        pp +=  (q.at(i)+" ");
    }
    ui ->textEdit->setText("  年龄最小的学生是：“"+pp+"”，其年龄是："+p +" 岁！");
    ui ->textEdit_2->setText("平均年龄为："+age+" 岁！");
    QMessageBox::information(this, "Tip", "查询成功！");

    mysql.clear();
    mmysql.clear();
    mmmysql.clear();
}


void MainWindow::on_pushButton_6_clicked()
{
    QString q;
    QString name = ui ->lineEdit_2 ->text();
    if(name != nullptr)
    {
        QSqlQuery mysql;
        //使用like关键字的模糊查询
        mysql.prepare("SELECT * FROM college WHERE `学院名称` LIKE :name;");

        //%的占位符问题解决
        mysql.bindValue(":name",QString("%%1%").arg(name));

        if(mysql.exec())
        {
            qDebug() << "模糊_Stu_Select success!";
        }
        else
        {
            qDebug() << "模糊_Stu_Select failed!";
        }
        ui ->tableWidget_7 ->clearContents();

        int row = 0;
        while (mysql.next())
        {
            ui ->tableWidget_7 ->setRowCount(row + 1);
            ui ->tableWidget_7 ->setItem(row, 0, new QTableWidgetItem(mysql.value("学院编号").toString()));
            ui ->tableWidget_7 ->setItem(row, 1, new QTableWidgetItem(mysql.value("学院名称").toString()));
            ui ->tableWidget_7 ->setItem(row, 2, new QTableWidgetItem(mysql.value("学院简介").toString()));
            row++;
        }
        q = QString::number(row, 10);
        ui->tableWidget_7->resizeColumnsToContents();
        mysql.clear();
    }
    else
    {
        ui ->tableWidget_7 ->clearContents();
        this ->getInfo_college();
        q = getCollegeCount();
    }
    ui ->label_ColCount->setText("共查询出 "+q+" 个学院！");
    QMessageBox::information(this, "Tip", "查询成功！");
//    this ->getInfo_college();
//    QMessageBox::information(this, "Tip", "查询成功！");
}


void MainWindow::on_pushButton_7_clicked()
{
    add_college *a = new add_college;
    a ->show();
}


void MainWindow::on_pushButton_8_clicked()
{
    MainWindow::rowData.clear();
    int currentRowIndex = ui ->tableWidget_7 ->currentRow();
    if(currentRowIndex > -1)
    {
        for(int i=0; i< ui ->tableWidget_7->columnCount();i++)
        {
            QTableWidgetItem *item=ui->tableWidget_7->item(currentRowIndex,i);
            MainWindow::rowData.append(item ->text());
        }
        qDebug() << MainWindow::rowData;
        update_college *u = new update_college;
        u ->show();
    }
    else
    {
        QMessageBox::warning(this, "warning", "请在显示框中选择要修改的学院信息！");
    }
}


void MainWindow::on_pushButton_9_clicked()
{
    MainWindow::rowData.clear();
    int currentRowIndex = ui ->tableWidget_7 ->currentRow();
    if(currentRowIndex > -1)
    {
        for(int i=0; i< ui ->tableWidget_7->columnCount();i++)
        {
            QTableWidgetItem *item=ui->tableWidget_7->item(currentRowIndex,i);
            MainWindow::rowData.append(item ->text());
        }
        qDebug() << MainWindow::rowData;
        delete_college *d = new delete_college();
        connect(d, &delete_college::collegeDeleted, this, &MainWindow::onCollegeDeleted);
        d ->show();
    }
    else
    {
        QMessageBox::warning(this, "warning", "请选择要删除的学院！");
    }
}


void MainWindow::on_outToExcel_btn_clicked()
{
    if(ui ->tableWidget ->rowCount() ==0 || ui ->tableWidget ->columnCount() ==0)
    {
        QMessageBox::information(this, "提示", "窗体中没有信息可以导出！");
        return;
    }
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Data"), ".", tr("(*.xlsx)"));
    if (!filePath.isEmpty())
    {
        QAxObject* excel = new QAxObject(this);
        excel->setControl("Excel.Application"); //Excel
        excel->dynamicCall("SetVisible(bool Visible)", false);
        excel->setProperty("DisplayAlerts", false);
        QAxObject* workbooks = excel->querySubObject("WorkBooks");
        workbooks->dynamicCall("Add");
        QAxObject* workbook = excel->querySubObject("ActiveWorkBook");
        QAxObject* worksheets = workbook->querySubObject("Sheets");
        QAxObject* worksheet = worksheets->querySubObject("Item(int)", 1);
        int rowCount = ui->tableWidget->rowCount();
        int columnCount = ui->tableWidget->columnCount();
        qDebug()<< rowCount;
        qDebug()<< columnCount;

        //设置表头值
        for(int i = 1; i < columnCount+1; i++)
        {
            QAxObject *Range = worksheet ->querySubObject("Cells(int,int)",1,i);
            Range ->dynamicCall("SetValue(const QString &)",ui ->tableWidget ->horizontalHeaderItem(i-1)->text());
        }
        //设置表格值
        for (int i = 1; i < rowCount + 1; ++i)
        {
            for (int j = 1; j < columnCount + 1; ++j)
            {
                //qDebug()<< "i = " << i<<"; j = "<<j;
                //QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i+1, j);
                QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i+1, j);
                Range->dynamicCall("SetValue(const QString &)", ui->tableWidget->item(i-1 , j - 1)->text());
            }
        }

        QAxObject *range = worksheet ->querySubObject("UsedRange");
        QAxObject *cells = range->querySubObject("Columns");
        cells ->dynamicCall("AutoFit");

        range ->setProperty("HorizontalAlignment",-4108);
        range ->setProperty("VerticalAlignment",-4108);

        workbook->dynamicCall("SaveAs(const QString &)", QDir::toNativeSeparators(filePath));//保存至路径
        workbook->dynamicCall("Close()");
        if (excel != NULL)
        {
            excel->dynamicCall("Quit(void)");
            delete excel;
            excel = nullptr;
        }
        QMessageBox::information(this, QStringLiteral("提示"), "成功导出数据至excel文件！");
    }

}


void MainWindow::on_outToTxt_btn_clicked()
{
    // 弹出文件对话框让用户选择保存路径和文件名
    QString filePath = QFileDialog::getSaveFileName(nullptr,
                                                    tr("Save Table Data"),
                                                    "output_" + QDateTime::currentDateTime().toString("MMdd_HHmmss") + ".txt",
                                                    tr("Text Files (*.txt);;All Files (*)"));

    if (filePath.isEmpty()) {
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, tr("Error"), tr("Failed to open the file for writing."));
        return;
    }

    QTextStream out(&file);

    // 先写入表头
    out <<"注：保存到txt文件格式易乱，可以导出至excel以规整格式！" <<"\n";
    out <<"以下信息从左至右依次为：( “";
    for (int column = 0; column < ui->tableWidget->columnCount(); ++column) {
        QTableWidgetItem *headerItem = ui->tableWidget->horizontalHeaderItem(column);
        if (headerItem) {
            out << headerItem->text() << "     ";
        }
    }
    out << "”)";
    out << "\n";

    const int rowCount = ui->tableWidget->rowCount();
    const int columnCount = ui->tableWidget->columnCount();

    // 再写入表格数据
    for (int row = 0; row < rowCount; ++row) {
        QString rowString;
        for (int column = 0; column < columnCount; ++column) {
            QTableWidgetItem *item = ui->tableWidget->item(row, column);
            if (item) {
                rowString += item->text() + "\t"; // 继续使用制表符分隔不同列
            }
        }
        rowString.chop(1); // 去掉最后一个多余的分隔符
        rowString += "\n";
        out << rowString;
    }

    file.close(); // 关闭文件
    QMessageBox::information(nullptr, tr("提示"), tr("成功导出数据至txt文件！"));
}


void MainWindow::on_pushButton_10_clicked()
{
    if(ui ->tableWidget_2 ->rowCount() ==0 || ui ->tableWidget_2 ->columnCount() ==0)
    {
        QMessageBox::information(this, "提示", "窗体中没有信息可以导出！");
        return;
    }
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Data"), ".", tr("(*.xlsx)"));
    if (!filePath.isEmpty())
    {
        QAxObject* excel = new QAxObject(this);
        excel->setControl("Excel.Application"); //Excel
        excel->dynamicCall("SetVisible(bool Visible)", false);
        excel->setProperty("DisplayAlerts", false);
        QAxObject* workbooks = excel->querySubObject("WorkBooks");
        workbooks->dynamicCall("Add");
        QAxObject* workbook = excel->querySubObject("ActiveWorkBook");
        QAxObject* worksheets = workbook->querySubObject("Sheets");
        QAxObject* worksheet = worksheets->querySubObject("Item(int)", 1);
        int rowCount = ui->tableWidget_2->rowCount();
        int columnCount = ui->tableWidget_2->columnCount();
        qDebug()<< rowCount;
        qDebug()<< columnCount;

        //设置表头值
        for(int i = 1; i < columnCount+1; i++)
        {
            QAxObject *Range = worksheet ->querySubObject("Cells(int,int)",1,i);
            Range ->dynamicCall("SetValue(const QString &)",ui ->tableWidget_2 ->horizontalHeaderItem(i-1)->text());
        }
        //设置表格值
        for (int i = 1; i < rowCount + 1; ++i)
        {
            for (int j = 1; j < columnCount + 1; ++j)
            {
                //QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i+1, j);
                QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i+1, j);
                Range->dynamicCall("SetValue(const QString &)", ui->tableWidget_2->item(i-1 , j - 1)->text());
            }
        }

        QAxObject *range = worksheet ->querySubObject("UsedRange");
        QAxObject *cells = range->querySubObject("Columns");
        cells ->dynamicCall("AutoFit");

        range ->setProperty("HorizontalAlignment",-4108);
        range ->setProperty("VerticalAlignment",-4108);

        workbook->dynamicCall("SaveAs(const QString &)", QDir::toNativeSeparators(filePath));//保存至路径
        workbook->dynamicCall("Close()");
        if (excel != NULL)
        {
            excel->dynamicCall("Quit(void)");
            delete excel;
            excel = nullptr;
        }
        QMessageBox::information(this, QStringLiteral("提示"), "成功导出数据至excel文件！");
    }

}


void MainWindow::on_pushButton_11_clicked()
{
    if(ui ->tableWidget_4 ->rowCount() ==0 || ui ->tableWidget_4 ->columnCount() ==0)
    {
        QMessageBox::information(this, "提示", "窗体中没有信息可以导出！");
        return;
    }
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Data"), ".", tr("(*.xlsx)"));
    if (!filePath.isEmpty())
    {
        QAxObject* excel = new QAxObject(this);
        excel->setControl("Excel.Application"); //Excel
        excel->dynamicCall("SetVisible(bool Visible)", false);
        excel->setProperty("DisplayAlerts", false);
        QAxObject* workbooks = excel->querySubObject("WorkBooks");
        workbooks->dynamicCall("Add");
        QAxObject* workbook = excel->querySubObject("ActiveWorkBook");
        QAxObject* worksheets = workbook->querySubObject("Sheets");
        QAxObject* worksheet = worksheets->querySubObject("Item(int)", 1);
        int rowCount = ui->tableWidget_4->rowCount();
        int columnCount = ui->tableWidget_4->columnCount();
        qDebug()<< rowCount;
        qDebug()<< columnCount;

        //设置表头值
        for(int i = 1; i < columnCount+1; i++)
        {
            QAxObject *Range = worksheet ->querySubObject("Cells(int,int)",1,i);
            Range ->dynamicCall("SetValue(const QString &)",ui ->tableWidget_4 ->horizontalHeaderItem(i-1)->text());
        }
        //设置表格值
        for (int i = 1; i < rowCount + 1; ++i)
        {
            for (int j = 1; j < columnCount + 1; ++j)
            {
                //QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i+1, j);
                QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i+1, j);
                Range->dynamicCall("SetValue(const QString &)", ui->tableWidget_4->item(i-1 , j - 1)->text());
            }
        }

        QAxObject *range = worksheet ->querySubObject("UsedRange");
        QAxObject *cells = range->querySubObject("Columns");
        cells ->dynamicCall("AutoFit");

        range ->setProperty("HorizontalAlignment",-4108);
        range ->setProperty("VerticalAlignment",-4108);

        workbook->dynamicCall("SaveAs(const QString &)", QDir::toNativeSeparators(filePath));//保存至路径
        workbook->dynamicCall("Close()");
        if (excel != NULL)
        {
            excel->dynamicCall("Quit(void)");
            delete excel;
            excel = nullptr;
        }
        QMessageBox::information(this, QStringLiteral("提示"), "成功导出数据至excel文件！");
    }
}


void MainWindow::on_pushButton_12_clicked()
{
    if(ui ->tableWidget_7 ->rowCount() ==0 || ui ->tableWidget_7 ->columnCount() ==0)
    {
        QMessageBox::information(this, "提示", "窗体中没有信息可以导出！");
        return;
    }
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Data"), ".", tr("(*.xlsx)"));
    if (!filePath.isEmpty())
    {
        QAxObject* excel = new QAxObject(this);
        excel->setControl("Excel.Application"); //Excel
        excel->dynamicCall("SetVisible(bool Visible)", false);
        excel->setProperty("DisplayAlerts", false);
        QAxObject* workbooks = excel->querySubObject("WorkBooks");
        workbooks->dynamicCall("Add");
        QAxObject* workbook = excel->querySubObject("ActiveWorkBook");
        QAxObject* worksheets = workbook->querySubObject("Sheets");
        QAxObject* worksheet = worksheets->querySubObject("Item(int)", 1);
        int rowCount = ui->tableWidget_7->rowCount();
        int columnCount = ui->tableWidget_7->columnCount();
        qDebug()<< rowCount;
        qDebug()<< columnCount;

        //设置表头值
        for(int i = 1; i < columnCount+1; i++)
        {
            QAxObject *Range = worksheet ->querySubObject("Cells(int,int)",1,i);
            Range ->dynamicCall("SetValue(const QString &)",ui ->tableWidget_7 ->horizontalHeaderItem(i-1)->text());
        }
        //设置表格值
        for (int i = 1; i < rowCount + 1; ++i)
        {
            for (int j = 1; j < columnCount + 1; ++j)
            {
                //QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i+1, j);
                QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i+1, j);
                Range->dynamicCall("SetValue(const QString &)", ui->tableWidget_7->item(i-1 , j - 1)->text());
            }
        }

        QAxObject *range = worksheet ->querySubObject("UsedRange");
        QAxObject *cells = range->querySubObject("Columns");
        cells ->dynamicCall("AutoFit");

        range ->setProperty("HorizontalAlignment",-4108);
        range ->setProperty("VerticalAlignment",-4108);

        workbook->dynamicCall("SaveAs(const QString &)", QDir::toNativeSeparators(filePath));//保存至路径
        workbook->dynamicCall("Close()");
        if (excel != NULL)
        {
            excel->dynamicCall("Quit(void)");
            delete excel;
            excel = nullptr;
        }
        QMessageBox::information(this, QStringLiteral("提示"), "成功导出数据至excel文件！");
    }
}


void MainWindow::on_pushButton_13_clicked()
{
    if(ui ->tableWidget_3 ->rowCount() ==0 || ui ->tableWidget_3 ->columnCount() ==0)
    {
        QMessageBox::information(this, "提示", "窗体中没有信息可以导出！");
        return;
    }
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Data"), ".", tr("(*.xlsx)"));
    if (!filePath.isEmpty())
    {
        QAxObject* excel = new QAxObject(this);
        excel->setControl("Excel.Application"); //Excel
        excel->dynamicCall("SetVisible(bool Visible)", false);
        excel->setProperty("DisplayAlerts", false);
        QAxObject* workbooks = excel->querySubObject("WorkBooks");
        workbooks->dynamicCall("Add");
        QAxObject* workbook = excel->querySubObject("ActiveWorkBook");
        QAxObject* worksheets = workbook->querySubObject("Sheets");
        QAxObject* worksheet = worksheets->querySubObject("Item(int)", 1);
        int rowCount = ui->tableWidget_3->rowCount();
        int columnCount = ui->tableWidget_3->columnCount();
        qDebug()<< rowCount;
        qDebug()<< columnCount;

        //设置表头值
        for(int i = 1; i < columnCount+1; i++)
        {
            QAxObject *Range = worksheet ->querySubObject("Cells(int,int)",1,i);
            Range ->dynamicCall("SetValue(const QString &)",ui ->tableWidget_3 ->horizontalHeaderItem(i-1)->text());
        }
        //设置表格值
        for (int i = 1; i < rowCount + 1; ++i)
        {
            for (int j = 1; j < columnCount + 1; ++j)
            {
                //QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i+1, j);
                QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i+1, j);
                Range->dynamicCall("SetValue(const QString &)", ui->tableWidget_3->item(i-1 , j - 1)->text());
            }
        }

        QAxObject *range = worksheet ->querySubObject("UsedRange");
        QAxObject *cells = range->querySubObject("Columns");
        cells ->dynamicCall("AutoFit");

        range ->setProperty("HorizontalAlignment",-4108);
        range ->setProperty("VerticalAlignment",-4108);

        workbook->dynamicCall("SaveAs(const QString &)", QDir::toNativeSeparators(filePath));//保存至路径
        workbook->dynamicCall("Close()");
        if (excel != NULL)
        {
            excel->dynamicCall("Quit(void)");
            delete excel;
            excel = nullptr;
        }
        QMessageBox::information(this, QStringLiteral("提示"), "成功导出数据至excel文件！");
    }
}


void MainWindow::on_pushButton_14_clicked()
{
    if(ui ->tableWidget_6 ->rowCount() ==0 || ui ->tableWidget_6 ->columnCount() ==0)
    {
        QMessageBox::information(this, "提示", "窗体中没有信息可以导出！");
        return;
    }
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Data"), ".", tr("(*.xlsx)"));
    if (!filePath.isEmpty())
    {
        QAxObject* excel = new QAxObject(this);
        excel->setControl("Excel.Application"); //Excel
        excel->dynamicCall("SetVisible(bool Visible)", false);
        excel->setProperty("DisplayAlerts", false);
        QAxObject* workbooks = excel->querySubObject("WorkBooks");
        workbooks->dynamicCall("Add");
        QAxObject* workbook = excel->querySubObject("ActiveWorkBook");
        QAxObject* worksheets = workbook->querySubObject("Sheets");
        QAxObject* worksheet = worksheets->querySubObject("Item(int)", 1);
        int rowCount = ui->tableWidget_6->rowCount();
        int columnCount = ui->tableWidget_6->columnCount();
        qDebug()<< rowCount;
        qDebug()<< columnCount;

        //设置表头值
        for(int i = 1; i < columnCount+1; i++)
        {
            QAxObject *Range = worksheet ->querySubObject("Cells(int,int)",1,i);
            Range ->dynamicCall("SetValue(const QString &)",ui ->tableWidget_6 ->horizontalHeaderItem(i-1)->text());
        }
        //设置表格值
        for (int i = 1; i < rowCount + 1; ++i)
        {
            for (int j = 1; j < columnCount + 1; ++j)
            {
                //QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i+1, j);
                QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i+1, j);
                Range->dynamicCall("SetValue(const QString &)", ui->tableWidget_6->item(i-1 , j - 1)->text());
            }
        }

        QAxObject *range = worksheet ->querySubObject("UsedRange");
        QAxObject *cells = range->querySubObject("Columns");
        cells ->dynamicCall("AutoFit");

        range ->setProperty("HorizontalAlignment",-4108);
        range ->setProperty("VerticalAlignment",-4108);

        workbook->dynamicCall("SaveAs(const QString &)", QDir::toNativeSeparators(filePath));//保存至路径
        workbook->dynamicCall("Close()");
        if (excel != NULL)
        {
            excel->dynamicCall("Quit(void)");
            delete excel;
            excel = nullptr;
        }
        QMessageBox::information(this, QStringLiteral("提示"), "成功导出数据至excel文件！");
    }
}

void MainWindow::onCollegeDeleted()
{
    QStringList a;
    QSqlQuery mysql;
    mysql.prepare("SELECT `学院名称` FROM college;");
    mysql.exec();
    while (mysql.next()) {
        a.append(mysql.value("学院名称").toString());
    }
    qDebug()<< "comboBox = " <<a;

    ui ->comboBox->clear();
    ui ->comboBox->addItem("全部学院");
    ui ->comboBox->addItems(a);
    mysql.clear();
}

void MainWindow::on_pushButton_15_clicked()
{
    QMap<QString, int> collegeCounts; // 用来存储每个学院及其对应的科技成果数量

    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QString collegeName = ui->tableWidget->item(row, 5)->text(); // 第五列是学院名称
        if (!collegeCounts.contains(collegeName)) {
            collegeCounts[collegeName] = 1;
        } else {
            collegeCounts[collegeName]++;
        }
//        qDebug() << "College:" << collegeName << ", Count:" << collegeCounts[collegeName];
    }

    // 创建柱状图
    QChart *chart = new QChart();

    // 设置标题样式
    // 设置标题字体样式
    QFont titleFont = chart->titleFont();
    titleFont.setPointSize(20); // 设置字体大小
    titleFont.setBold(true); // 设置加粗

    // 设置标题颜色为蓝色（例如）
    QBrush titleBrush(Qt::red); // 创建一个蓝色画刷
    chart->setTitleBrush(titleBrush); // 设置标题画刷，这将影响标题的字体颜色
    chart->setTitleFont(titleFont);
    chart->setTitle("科技成果按学院分布");

    // 创建一个QBarSet来存储所有学院的数据点
    QBarSet *set = new QBarSet("科技成果数量");

    foreach (QString college, collegeCounts.keys()) {
        set->append(collegeCounts[college]); // 添加每个学院的科技成果数量
    }

    // 创建一个QBarSeries并将QBarSet添加到其中
    QBarSeries *series = new QBarSeries();
    series->append(set);

    chart->addSeries(series);

    // 设置轴
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    for (const QString &college : collegeCounts.keys()) {
        axisX->append(college); // 添加每个学院名称作为X轴标签
//        qDebug() << "Append to X-axis:" << college; // 打印添加到X轴的每个学院名称
    }
    axisX->setTitleText("学院名称"); // 设置X轴图例
    // 设置轴标签的字体和颜色
    QFont font;
    font.setPointSize(10); // 设置字体大小
    axisX->setLabelsFont(font); // 设置轴标签的字体
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("成果数量"); // 设置Y轴图例
    axisY->setLabelsFont(font); // 设置轴标签的字体
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);


    // 显示图表
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000, 600);
    chartView->setWindowTitle("柱状图");
    chartView->show();
}


void MainWindow::on_pushButton_16_clicked()
{
    QMap<QString, int> collegeCounts; // 存储学院及其科技成果数量

    // 遍历表格的每一行
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        // 获取学院名称
        QString collegeName = ui->tableWidget->item(row, 5)->text(); // 假设学院名称在第6列（索引为5）

        // 累加科技成果数量
        collegeCounts[collegeName] += 1;
    }

    // 创建饼状图
    QChart *chart = new QChart();
    // 设置标题样式
    // 设置标题字体样式
    QFont titleFont = chart->titleFont();
    titleFont.setPointSize(20); // 设置字体大小
    titleFont.setBold(true); // 设置加粗

    // 设置标题颜色为蓝色（例如）
    QBrush titleBrush(Qt::red); // 创建一个蓝色画刷
    chart->setTitleBrush(titleBrush); // 设置标题画刷，这将影响标题的字体颜色
    chart->setTitleFont(titleFont);
    chart->setTitle("科技成果按学院分布");
    chart->setAnimationOptions(QChart::AllAnimations);

    // 创建QPieSeries对象并添加数据
    QPieSeries *series = new QPieSeries();
    for (const QString &college : collegeCounts.keys()) {
        series->append(college, collegeCounts[college]);
    }
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // 显示图表
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // 调整窗口大小以适应图表视图
    chartView->resize(800, 600);

    chartView->setWindowTitle("饼状图");
    chartView->show();
}


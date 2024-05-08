#include "stumainwindow.h"
#include "ui_stumainwindow.h"
//#include "mainwindow.h"
#include <QMessageBox>
#include "apply_achievement.h"
#include "mainwindow.h"
#include "apply_gain.h"
#include<QAxObject>
#include<QFileDialog>

QString StuMainwindow::stuAccount=NULL;
StuMainwindow::StuMainwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StuMainwindow)
{
    this ->setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);

    stu_sql::Connection();

    this ->setStuInfo_table();
    this ->setStuInfo_table2();
    this ->setStuInfo_table3();
    this ->setStuInfo_table4();
    this ->setStuInfo_table5();

    QString q;
    q = getName();
    ui ->label_5->setText("[学号："+StuMainwindow::stuAccount+"   "+"姓名："+q+"]");

    QSqlQuery mysql;
    QStringList a;
    mysql.prepare("SELECT `学院名称` FROM college;");
    mysql.exec();
    while (mysql.next()) {
        a.append(mysql.value("学院名称").toString());
    }

    ui ->comboBox->addItems(a);

}

StuMainwindow::~StuMainwindow()
{
    delete ui;
}

void StuMainwindow::on_exit_btn_clicked()
{
    exit(0);
}

void  StuMainwindow::setStuInfo_table()
{
    ui ->tableWidget ->setColumnCount(10);//列数

    //表头
    ui ->tableWidget ->setHorizontalHeaderLabels(QStringList()<< "学号" <<  "姓名" << "性别" << "学院名称"
                                                             << "科研小组名称" << "指导教师"
                                                             << "成果名称"<< "审批结果" << "获得成果时间" << "成果简介");
    //表中信息
    this ->getStuInfo_database();
    //表格信息不可以被编辑
    ui ->tableWidget ->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void StuMainwindow::setStuInfo_table2()
{
    ui ->tableWidget_2 ->setColumnCount(12);//列数

    //表头
    ui ->tableWidget_2 ->setHorizontalHeaderLabels(QStringList()<< "学号" << "密码" << "姓名" << "性别" << "年龄" << "学院名称" <<"科研小组组号" << "小组名称" << "指导教师" << "成果名称" << "获得时间" << "成果简介");
    //表中信息
    this ->getMyInfo();
    //表格信息不可以被编辑
    ui ->tableWidget_2 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void StuMainwindow::setStuInfo_table3()
{
    ui ->tableWidget_3 ->setColumnCount(3);//列数

    //表头
    ui ->tableWidget_3 ->setHorizontalHeaderLabels(QStringList()<< "小组编号" << "小组名称" << "指导教师" );
    //表中信息
    this ->getInfoGroup();
    //表格信息不可以被编辑
    ui ->tableWidget_3 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void StuMainwindow::setStuInfo_table4()
{
    ui ->tableWidget_4 ->setColumnCount(5);//列数

    //表头
    ui ->tableWidget_4 ->setHorizontalHeaderLabels(QStringList()<< "审批意见" << "成果编号" << "成果名称" << "获得时间" << "简介" );
    //表中信息
    this ->getInfoAchiv();
    //表格信息不可以被编辑
    ui ->tableWidget_4 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void StuMainwindow::setStuInfo_table5()
{
    ui ->tableWidget_5 ->setColumnCount(3);//列数

    ui ->tableWidget_5 ->setHorizontalHeaderLabels(QStringList()<< "学院编号" << "学院名称" <<  "学院简介" );
    this ->getInfoCollege();
    ui ->tableWidget_5 ->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void StuMainwindow::getStuInfo_database()
{
    QSqlQuery mysql;
    //连接查询
    mysql.prepare("SELECT students.`学号`,students.`姓名`,students.`性别`,college.`学院名称`,s_groups.`小组名称`,s_groups.`指导教师`,achievement.`成果名称`,gain.`审批结果`,achievement.`时间`,achievement.`简介` "
                  "FROM students,college,s_groups,gain,achievement "
                  "WHERE students.`科研小组号`=s_groups.`小组编号` "
                  "AND students.`学院编号` = college.`学院编号` "
                  "AND s_groups.`小组编号`=gain.`科研小组组号` "
                  "AND gain.`成果编号`=achievement.`成果编号` "
                  "AND gain.`审批结果`='通过' "
                  "ORDER BY students.`学号` ASC;");

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
        ui ->tableWidget ->setItem(row, 1, new QTableWidgetItem(mysql.value("姓名").toString()));
        ui ->tableWidget ->setItem(row, 2, new QTableWidgetItem(mysql.value("性别").toString()));
        ui ->tableWidget ->setItem(row, 3, new QTableWidgetItem(mysql.value("学院名称").toString()));
        ui ->tableWidget ->setItem(row, 4, new QTableWidgetItem(mysql.value("小组名称").toString()));
        ui ->tableWidget ->setItem(row, 5, new QTableWidgetItem(mysql.value("指导教师").toString()));
        ui ->tableWidget ->setItem(row, 6, new QTableWidgetItem(mysql.value("成果名称").toString()));
        ui ->tableWidget ->setItem(row, 7, new QTableWidgetItem(mysql.value("审批结果").toString()));
        ui ->tableWidget ->setItem(row, 8, new QTableWidgetItem(mysql.value("时间").toString()));
        ui ->tableWidget ->setItem(row, 9, new QTableWidgetItem(mysql.value("简介").toString()));
        row++;
    }
    ui->tableWidget->resizeColumnsToContents();
    mysql.clear();
}

void StuMainwindow::getMyInfo()
{
    QSqlQuery mysql;
    QSqlQuery mysql_2;
    QSqlQuery mysql_3;
    QSqlQuery mysql_4;
    QSqlQuery mysql_5;
    //连接查询
    mysql.prepare("SELECT * FROM students WHERE `学号`=:number;");
    mysql.bindValue(":number",StuMainwindow::stuAccount);

    //qDebug() << mysql.value("科研小组号").toInt();
    qDebug() << StuMainwindow::stuAccount;
    if(mysql.exec())
    {
        qDebug() << "Myinfo_Select success!";
    }
    else
    {
        qDebug() << "Myinfo_Select failed!";
    }
    mysql.next();

    mysql_2.prepare("SELECT * FROM s_groups WHERE `小组编号` = :num;");
    mysql_2.bindValue(":num",mysql.value("科研小组号").toInt());
    mysql_2.exec();
    mysql_2.next();

    mysql_3.prepare("SELECT * FROM gain WHERE `科研小组组号` = :nu AND gain.`审批结果`='通过';");
    mysql_3.bindValue(":nu",mysql.value("科研小组号").toInt());
    mysql_3.exec();
    int a[100] = {0};
    int k=0;
    while(mysql_3.next())
    {
        a[k] = mysql_3.value("成果编号").toInt();
        qDebug()<<"a["<<k<<"] = "<< a[k];
        k++;
    }

    mysql_5.prepare("SELECT * FROM college WHERE `学院编号` = :n;");
    mysql_5.bindValue(":n",mysql.value("学院编号").toInt());
    mysql_5.exec();
    mysql_5.next();

    int row = 0; //行数
    k=0;

    if(a[0]==0)
    {
        ui ->tableWidget_2 ->setRowCount(row + 1);
        ui ->tableWidget_2 ->setItem(row, 0, new QTableWidgetItem(mysql.value("学号").toString()));
        ui ->tableWidget_2 ->setItem(row, 1, new QTableWidgetItem(mysql.value("密码").toString()));
        ui ->tableWidget_2 ->setItem(row, 2, new QTableWidgetItem(mysql.value("姓名").toString()));
        ui ->tableWidget_2 ->setItem(row, 3, new QTableWidgetItem(mysql.value("性别").toString()));
        ui ->tableWidget_2 ->setItem(row, 4, new QTableWidgetItem(mysql.value("年龄").toString()));
        ui ->tableWidget_2 ->setItem(row, 5, new QTableWidgetItem(mysql_5.value("学院名称").toString()));
        ui ->tableWidget_2 ->setItem(row, 6, new QTableWidgetItem(mysql.value("科研小组号").toString()));
        ui ->tableWidget_2 ->setItem(row, 7, new QTableWidgetItem(mysql_2.value("小组名称").toString()));
        ui ->tableWidget_2 ->setItem(row, 8, new QTableWidgetItem(mysql_2.value("指导教师").toString()));
    }

    while(a[k]!=0)
    {
        mysql_4.prepare("SELECT * FROM achievement WHERE `成果编号` = :n;");
        mysql_4.bindValue(":n",a[k++]);
        mysql_4.exec();
//    mysql_4.next();
        while (mysql_4.next())
        {
            ui ->tableWidget_2 ->setRowCount(row + 1);
            ui ->tableWidget_2 ->setItem(row, 0, new QTableWidgetItem(mysql.value("学号").toString()));
            ui ->tableWidget_2 ->setItem(row, 1, new QTableWidgetItem(mysql.value("密码").toString()));
            ui ->tableWidget_2 ->setItem(row, 2, new QTableWidgetItem(mysql.value("姓名").toString()));
            ui ->tableWidget_2 ->setItem(row, 3, new QTableWidgetItem(mysql.value("性别").toString()));
            ui ->tableWidget_2 ->setItem(row, 4, new QTableWidgetItem(mysql.value("年龄").toString()));
            ui ->tableWidget_2 ->setItem(row, 5, new QTableWidgetItem(mysql_5.value("学院名称").toString()));
            ui ->tableWidget_2 ->setItem(row, 6, new QTableWidgetItem(mysql.value("科研小组号").toString()));
            ui ->tableWidget_2 ->setItem(row, 7, new QTableWidgetItem(mysql_2.value("小组名称").toString()));
            ui ->tableWidget_2 ->setItem(row, 8, new QTableWidgetItem(mysql_2.value("指导教师").toString()));
            ui ->tableWidget_2 ->setItem(row, 9, new QTableWidgetItem(mysql_4.value("成果名称").toString()));
            ui ->tableWidget_2 ->setItem(row, 10, new QTableWidgetItem(mysql_4.value("时间").toString()));
            ui ->tableWidget_2 ->setItem(row, 11, new QTableWidgetItem(mysql_4.value("简介").toString()));
            row++;
        }
    }

    ui->tableWidget_2->resizeColumnsToContents();
    mysql.clear();
}

QString StuMainwindow::getName()
{
    QSqlQuery mysql;
    mysql.prepare("SELECT * FROM students WHERE `学号`=:number;");
    mysql.bindValue(":number",StuMainwindow::stuAccount);
    mysql.exec();
    mysql.next();
//    ui ->tableWidget_5 ->setItem(0, 0, new QTableWidgetItem(mysql.value("学号").toString()));
//    ui ->tableWidget_5 ->setItem(0, 0, new QTableWidgetItem(mysql.value("姓名").toString()));

//    ui->tableWidget_5->resizeColumnsToContents();

   // mysql.clear();
    return mysql.value("姓名").toString();
}

QString StuMainwindow::getStudentCount()
{
    QSqlQuery mysql;
    mysql.prepare("SELECT count(*)"
                  "FROM students,college,s_groups,gain,achievement "
                  "WHERE students.`科研小组号`=s_groups.`小组编号` "
                  "AND students.`学院编号` = college.`学院编号` "
                  "AND s_groups.`小组编号`=gain.`科研小组组号` "
                  "AND gain.`成果编号`=achievement.`成果编号` "
                  "ORDER BY students.`学号` ASC;");
    mysql.exec();
    mysql.next();

    qDebug() << "学生数量："+mysql.value("count(*)").toString();
                               return mysql.value("count(*)").toString();
}

void StuMainwindow::getInfoGroup()
{
    QSqlQuery mysql;
    QString q;
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
    q = QString::number(row, 10);
    ui ->label_groupCount ->setText("--系统中存在 "+q +" 个科研小组！--");
    ui->tableWidget_3->resizeColumnsToContents();
    mysql.clear();
}

void StuMainwindow::getInfoAchiv()
{
    QSqlQuery mysql;
    QString q;
    mysql.prepare("SELECT * "
                  "FROM achievement WHERE achievement.`审批意见`='通过';");

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
    q = QString::number(row, 10);
    ui ->label_achievementCount ->setText("--系统中存在 "+q +" 个已过审的科研成果!--");
    ui->tableWidget_4->resizeColumnsToContents();
    mysql.clear();
}

void StuMainwindow::getInfoCollege()
{
    QSqlQuery mysql;
    mysql.prepare("SELECT * "
                  "FROM college;");

    if(mysql.exec())
    {
        qDebug() << "College_Select success!";
    }
    else
    {
        qDebug() << "College_Select failed!";
    }

    int row = 0;
    while (mysql.next())
    {
        ui ->tableWidget_5 ->setRowCount(row + 1);
        ui ->tableWidget_5 ->setItem(row, 0, new QTableWidgetItem(mysql.value("学院编号").toString()));
        ui ->tableWidget_5 ->setItem(row, 1, new QTableWidgetItem(mysql.value("学院名称").toString()));
        ui ->tableWidget_5 ->setItem(row, 2, new QTableWidgetItem(mysql.value("学院简介").toString()));
        row++;
    }
    ui->tableWidget_5->resizeColumnsToContents();
    mysql.clear();
}

QString StuMainwindow::getCollegeCounts()
{
    QSqlQuery mysql;
    mysql.prepare("SELECT count(*) FROM college;");
    mysql.exec();
    mysql.next();

    qDebug() << "学院数量："+mysql.value("count(*)").toString();
    return mysql.value("count(*)").toString();
}

void StuMainwindow::on_sql_btnqiaotao_clicked()
{
    QSqlQuery mysql;
    //嵌套查询
    ui ->tableWidget ->clear();
    ui ->tableWidget ->setColumnCount(5);//列数

    //表头
    ui ->tableWidget ->setHorizontalHeaderLabels(QStringList()<< "学号" <<  "姓名" << "性别"
                                                             << "科研小组编号" << "学院编号");

    mysql.prepare("SELECT students.`学号`,students.`姓名`,students.`性别`,students.`科研小组号`,students.`学院编号` FROM students WHERE `科研小组号` IN ( SELECT `小组编号` FROM s_groups WHERE `小组编号` IN ( SELECT `科研小组组号` FROM gain WHERE `成果编号` IN ( SELECT `成果编号` FROM achievement )));");

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
        ui ->tableWidget ->setItem(row, 1, new QTableWidgetItem(mysql.value("姓名").toString()));
        ui ->tableWidget ->setItem(row, 2, new QTableWidgetItem(mysql.value("性别").toString()));
        ui ->tableWidget ->setItem(row, 3, new QTableWidgetItem(mysql.value("科研小组号").toString()));
        ui ->tableWidget ->setItem(row, 4, new QTableWidgetItem(mysql.value("学院编号").toString()));
        row++;
    }
    ui->tableWidget->resizeColumnsToContents();
    QMessageBox::information(this, "Tip", "操作成功！");
    mysql.clear();
}


void StuMainwindow::on_search_btn_clicked()
{
    this ->setStuInfo_table();
    QSqlQuery mysql;
    QString q;
    QString name = ui ->lineEdit_2->text();
    QString college = ui->comboBox->currentText();

    if(!name.isEmpty())
    {
        if(college == "全部学院")
        {
            //使用like关键字的模糊查询
            mysql.prepare("SELECT students.`学号`,students.`姓名`,students.`性别`,college.`学院名称`,s_groups.`小组名称`,s_groups.`指导教师`,achievement.`成果名称`,gain.`审批结果`,achievement.`时间`,achievement.`简介` FROM students,college,s_groups,gain,achievement WHERE students.`科研小组号`=s_groups.`小组编号` AND students.`学院编号` = college.`学院编号` AND s_groups.`小组编号`=gain.`科研小组组号` AND gain.`成果编号`=achievement.`成果编号` AND gain.`审批结果`='通过' AND `姓名` LIKE :name ORDER BY students.`学号` ASC;");

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
            ui ->tableWidget ->clearContents();
            ui ->tableWidget ->setRowCount(0);

            int row = 0;
            while (mysql.next())
            {
                ui ->tableWidget ->setRowCount(row + 1);
                ui ->tableWidget ->setItem(row, 0, new QTableWidgetItem(mysql.value("学号").toString()));
                ui ->tableWidget ->setItem(row, 1, new QTableWidgetItem(mysql.value("姓名").toString()));
                ui ->tableWidget ->setItem(row, 2, new QTableWidgetItem(mysql.value("性别").toString()));
                ui ->tableWidget ->setItem(row, 3, new QTableWidgetItem(mysql.value("学院名称").toString()));
                ui ->tableWidget ->setItem(row, 4, new QTableWidgetItem(mysql.value("小组名称").toString()));
                ui ->tableWidget ->setItem(row, 5, new QTableWidgetItem(mysql.value("指导教师").toString()));
                ui ->tableWidget ->setItem(row, 6, new QTableWidgetItem(mysql.value("成果名称").toString()));
                ui ->tableWidget ->setItem(row, 7, new QTableWidgetItem(mysql.value("审批结果").toString()));
                ui ->tableWidget ->setItem(row, 8, new QTableWidgetItem(mysql.value("时间").toString()));
                ui ->tableWidget ->setItem(row, 9, new QTableWidgetItem(mysql.value("简介").toString()));
                row++;
            }
            q = QString::number(row, 10);
            ui->tableWidget->resizeColumnsToContents();
            mysql.clear();
        }
        else
        {
            //使用like关键字的模糊查询
            mysql.prepare("SELECT students.`学号`,students.`姓名`,students.`性别`,college.`学院名称`,s_groups.`小组名称`,s_groups.`指导教师`,achievement.`成果名称`,gain.`审批结果`,achievement.`时间`,achievement.`简介` FROM students,college,s_groups,gain,achievement WHERE students.`科研小组号`=s_groups.`小组编号` AND students.`学院编号` = college.`学院编号` AND s_groups.`小组编号`=gain.`科研小组组号` AND gain.`成果编号`=achievement.`成果编号` AND gain.`审批结果`='通过' AND `姓名` LIKE :name AND `学院名称`=:col_name ORDER BY students.`学号` ASC;");

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
            ui ->tableWidget ->setRowCount(0);

            int row = 0;
            while (mysql.next())
            {
                ui ->tableWidget ->setRowCount(row + 1);
                ui ->tableWidget ->setItem(row, 0, new QTableWidgetItem(mysql.value("学号").toString()));
                ui ->tableWidget ->setItem(row, 1, new QTableWidgetItem(mysql.value("姓名").toString()));
                ui ->tableWidget ->setItem(row, 2, new QTableWidgetItem(mysql.value("性别").toString()));
                ui ->tableWidget ->setItem(row, 3, new QTableWidgetItem(mysql.value("学院名称").toString()));
                ui ->tableWidget ->setItem(row, 4, new QTableWidgetItem(mysql.value("小组名称").toString()));
                ui ->tableWidget ->setItem(row, 5, new QTableWidgetItem(mysql.value("指导教师").toString()));
                ui ->tableWidget ->setItem(row, 6, new QTableWidgetItem(mysql.value("成果名称").toString()));
                ui ->tableWidget ->setItem(row, 7, new QTableWidgetItem(mysql.value("审批结果").toString()));
                ui ->tableWidget ->setItem(row, 8, new QTableWidgetItem(mysql.value("时间").toString()));
                ui ->tableWidget ->setItem(row, 9, new QTableWidgetItem(mysql.value("简介").toString()));
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
            this ->getStuInfo_database();
            q = getStudentCount();
        }
        else
        {
            //使用like关键字的模糊查询
            mysql.prepare("SELECT students.`学号`,students.`姓名`,students.`性别`,college.`学院名称`,s_groups.`小组名称`,s_groups.`指导教师`,achievement.`成果名称`,gain.`审批结果`,achievement.`时间`,achievement.`简介` FROM students,college,s_groups,gain,achievement WHERE students.`科研小组号`=s_groups.`小组编号` AND students.`学院编号` = college.`学院编号` AND s_groups.`小组编号`=gain.`科研小组组号` AND gain.`成果编号`=achievement.`成果编号` AND gain.`审批结果`='通过' AND `学院名称`=:col_name ORDER BY students.`学号` ASC;");

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
            ui ->tableWidget ->setRowCount(0);

            int row = 0;
            while (mysql.next())
            {
                ui ->tableWidget ->setRowCount(row + 1);
                ui ->tableWidget ->setItem(row, 0, new QTableWidgetItem(mysql.value("学号").toString()));
                ui ->tableWidget ->setItem(row, 1, new QTableWidgetItem(mysql.value("姓名").toString()));
                ui ->tableWidget ->setItem(row, 2, new QTableWidgetItem(mysql.value("性别").toString()));
                ui ->tableWidget ->setItem(row, 3, new QTableWidgetItem(mysql.value("学院名称").toString()));
                ui ->tableWidget ->setItem(row, 4, new QTableWidgetItem(mysql.value("小组名称").toString()));
                ui ->tableWidget ->setItem(row, 5, new QTableWidgetItem(mysql.value("指导教师").toString()));
                ui ->tableWidget ->setItem(row, 6, new QTableWidgetItem(mysql.value("成果名称").toString()));
                ui ->tableWidget ->setItem(row, 7, new QTableWidgetItem(mysql.value("审批结果").toString()));
                ui ->tableWidget ->setItem(row, 8, new QTableWidgetItem(mysql.value("时间").toString()));
                ui ->tableWidget ->setItem(row, 9, new QTableWidgetItem(mysql.value("简介").toString()));
                row++;
            }
            q = QString::number(row, 10);
            ui->tableWidget->resizeColumnsToContents();
            mysql.clear();
        }
    }
    ui ->label_9->setText("--共 "+q+" 条数据！--");
    QMessageBox::information(this, "Tip", "查询成功！");
}


void StuMainwindow::on_pushButton_clicked()
{
    this ->getMyInfo();
    QMessageBox::information(this, "Tip", "查询成功！");
}


void StuMainwindow::on_pushButton_2_clicked()
{
    QString my_pass = ui ->lineEdit ->text();
    QSqlQuery mysql;
    if(my_pass != nullptr)
    {
        mysql.prepare("UPDATE students SET `密码`=:name WHERE `学号`=:num;");
        mysql.bindValue(":name", my_pass);
        mysql.bindValue(":num", StuMainwindow::stuAccount);
    }
    else
    {
        QMessageBox::warning(this,"warning","请输入要修改的密码！");
    }

    bool ifupdate = mysql.exec();
    if(ifupdate)
    {
        QMessageBox::information(this, "提示", "修改成功！！");
        qDebug() << "update successfully!!";
    }
    else
    {
        qDebug() << "update failed!!";
    }
    ui ->lineEdit ->clear();
}


void StuMainwindow::on_pushButton_3_clicked()
{
    page_login *p =new page_login;
    p->show();
    this ->close();
}


void StuMainwindow::on_pushButton_4_clicked()
{
    this ->getInfoGroup();
    this ->getInfoAchiv();
    QMessageBox::information(this, "Tip", "查询成功！");
}



void StuMainwindow::on_pushButton_5_clicked()
{
    QString q;
    QString name = ui ->lineEdit_3 ->text();
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
        ui ->tableWidget_5 ->clearContents();

        int row = 0;
        while (mysql.next())
        {
            ui ->tableWidget_5 ->setRowCount(row + 1);
            ui ->tableWidget_5 ->setItem(row, 0, new QTableWidgetItem(mysql.value("学院编号").toString()));
            ui ->tableWidget_5 ->setItem(row, 1, new QTableWidgetItem(mysql.value("学院名称").toString()));
            ui ->tableWidget_5 ->setItem(row, 2, new QTableWidgetItem(mysql.value("学院简介").toString()));
            row++;
        }
        q = QString::number(row, 10);
        ui->tableWidget_5->resizeColumnsToContents();
        mysql.clear();
    }
    else
    {
        ui ->tableWidget_5 ->clearContents();
        this ->getInfoCollege();
        q = getCollegeCounts();
    }
    ui ->label_ColCount->setText("--共查询出 "+q+" 个学院！--");
    QMessageBox::information(this, "Tip", "查询成功！");
}



void StuMainwindow::on_btn_applyForAchi_clicked()
{
    apply_Achievement *a = new apply_Achievement;
    a ->show();
}


void StuMainwindow::on_pushButton_6_clicked()
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
        apply_Gain *a = new apply_Gain;
        a ->show();
    }
    else
    {
        QMessageBox::warning(this, "warning", "请在右侧显示框中选择要绑定的科技成果！");
    }
}


void StuMainwindow::on_pushButton_7_clicked()
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
                //QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i+1, j);
                QAxObject* Range = worksheet->querySubObject("Cells(int,int)", i+1, j);
                Range->dynamicCall("SetValue(const QString &)", ui->tableWidget->item(i-1 , j - 1)->text());
                //qDebug()<< "item( " << i-1<< "," << j-1 <<") = "<<ui->tableWidget->item(i-1 , j - 1)->text();
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


#include "update_group.h"
#include "ui_update_group.h"
#include "mainwindow.h"
#include <QMessageBox>

update_group::update_group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::update_group)
{
    ui->setupUi(this);

    if(!MainWindow::rowData.empty())
    {
        ui ->num_line ->setText(MainWindow::rowData.at(0));
        ui ->group_nameOfupdate ->setText(MainWindow::rowData.at(1));
        ui ->te_nameOfupdate ->setText(MainWindow::rowData.at(2));

        ui ->num_line ->setEnabled(false);
    }
}

update_group::~update_group()
{
    delete ui;
}

void update_group::on_pushButton_clicked()
{
    this ->close();
}


void update_group::on_pushButton_2_clicked()
{
        QString group_num = ui ->num_line ->text();
        QString group_nam = ui ->group_nameOfupdate ->text();
        QString group_tea = ui ->te_nameOfupdate ->text();

        QSqlQuery mysql;
        if(group_num != nullptr)
        {
            if(group_nam != nullptr && group_tea == nullptr)
            {
                mysql.prepare("UPDATE s_groups SET `小组名称`=:name WHERE `小组编号`=:num;");
                mysql.bindValue(":name", group_nam);
                mysql.bindValue(":num", group_num);
            }
            else if(group_nam == nullptr && group_tea != nullptr)
            {
                mysql.prepare("UPDATE s_groups SET `指导教师`=:name WHERE `小组编号`=:num;");
                mysql.bindValue(":name", group_tea);
                mysql.bindValue(":num", group_num);
            }
            else if(group_nam != nullptr && group_tea != nullptr)
            {
                mysql.prepare("UPDATE s_groups SET `小组名称`=:name,`指导教师`=:nam WHERE `小组编号`=:num;");
                mysql.bindValue(":name", group_nam);
                mysql.bindValue(":nam", group_tea);
                mysql.bindValue(":num", group_num);
            }
            else
            {
                QMessageBox::warning(this, "warning", "请输入要修改的内容！");
            }

        }
        else if(group_num == nullptr)
        {
            QMessageBox::warning(this, "warning", "请输入要修改的小组编号！");
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


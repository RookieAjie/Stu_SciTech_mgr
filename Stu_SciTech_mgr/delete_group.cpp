#include "delete_group.h"
#include "ui_delete_group.h"
#include "mainwindow.h"
#include <QMessageBox>

delete_group::delete_group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::delete_group)
{
    ui->setupUi(this);

    if(!MainWindow::rowData.empty())
    {
        ui ->lineEdit ->setText(MainWindow::rowData.at(0));
        ui ->lineEdit_2 ->setText(MainWindow::rowData.at(1));
        ui ->lineEdit_3 ->setText(MainWindow::rowData.at(2));

        ui ->lineEdit ->setEnabled(false);
        ui ->lineEdit_2 ->setEnabled(false);
        ui ->lineEdit_3 ->setEnabled(false);

    }
}

delete_group::~delete_group()
{
    delete ui;
}

void delete_group::on_pushButton_clicked()
{
    this ->close();
}


void delete_group::on_pushButton_2_clicked()
{
    if(QMessageBox::Yes == QMessageBox::question(this, "警告", "您确定要删除吗？"))
    {
        QString group_num = ui ->lineEdit ->text();
        QSqlQuery mysql;
        QSqlQuery mysql2;
        QSqlQuery mysql3;
        if(group_num == nullptr)
        {
            QMessageBox::warning(this,"warning", "请输入要删除的小组编号！");
        }
        else
        {
            mysql3.prepare("UPDATE students SET `科研小组号` = NULL WHERE `科研小组号` =:numb");
            mysql3.bindValue(":numb", group_num);
            mysql2.prepare("DELETE FROM gain WHERE `科研小组组号` = :numbe");
            mysql2.bindValue(":numbe", group_num);
            mysql.prepare("DELETE FROM s_groups WHERE `小组编号` = :number");
            mysql.bindValue(":number", group_num);
            mysql3.exec();
            mysql2.exec();

        }


        bool ifdel = mysql.exec();
        if(ifdel)
        {
            QMessageBox::information(this, "提示", "删除成功！！");
            qDebug() << "delete successfully!!";
            this ->close();
        }
        else
        {
            QMessageBox::critical(this, "错误", "删除失败！请检查编号正确性！");
            qDebug() << "delete failed!!";
        }
    }

}


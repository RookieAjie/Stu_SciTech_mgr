#include "delete_stu.h"
#include "ui_delete_stu.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QMessageBox>

delete_Stu::delete_Stu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::delete_Stu)
{
    ui->setupUi(this);

    if(!MainWindow::rowData.empty())
    {
        ui ->lineEdit ->setText(MainWindow::rowData.at(0));
        ui ->lineEdit_2 ->setText(MainWindow::rowData.at(1));
        ui ->lineEdit_3 ->setText(MainWindow::rowData.at(2));
        ui ->lineEdit_4 ->setText(MainWindow::rowData.at(3));
        ui ->lineEdit_5 ->setText(MainWindow::rowData.at(4));
        ui ->lineEdit_6 ->setText(MainWindow::rowData.at(5));
        ui ->lineEdit_7 ->setText(MainWindow::rowData.at(6));

        ui ->lineEdit ->setEnabled(false);
        ui ->lineEdit_2 ->setEnabled(false);
        ui ->lineEdit_3 ->setEnabled(false);
        ui ->lineEdit_4 ->setEnabled(false);
        ui ->lineEdit_5 ->setEnabled(false);
        ui ->lineEdit_6 ->setEnabled(false);
        ui ->lineEdit_7 ->setEnabled(false);
    }
}

delete_Stu::~delete_Stu()
{
    delete ui;
}

void delete_Stu::on_pushButton_clicked()
{
    if(QMessageBox::Yes == QMessageBox::question(this, "警告", "您确定要删除吗？"))
    {
        QString stu_num = ui ->lineEdit ->text();
        QSqlQuery mysql;
        mysql.prepare("DELETE FROM students WHERE `学号` = :number");
        mysql.bindValue(":number", stu_num);
        bool ifdel = mysql.exec();
        ui ->lineEdit ->clear();
        if(ifdel)
        {
            QMessageBox::information(this, "提示", "删除成功！！");
            qDebug() << "delete successfully!!";
            this ->close();
        }
        else
        {
            qDebug() << "delete failed!!";
        }
    }

}


void delete_Stu::on_pushButton_2_clicked()
{
    this ->close();
}


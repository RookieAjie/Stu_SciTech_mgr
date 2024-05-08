#include "delete_admin.h"
#include "ui_delete_admin.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QMessageBox>

delete_admin::delete_admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::delete_admin)
{
    ui->setupUi(this);

    if(!MainWindow::rowData.empty())
    {
        ui ->lineEdit ->setText(MainWindow::rowData.at(0));
        ui ->lineEdit_2 ->setText(MainWindow::rowData.at(1));

        ui ->lineEdit ->setEnabled(false);
        ui ->lineEdit_2 ->setEnabled(false);
    }
}

delete_admin::~delete_admin()
{
    delete ui;
}

void delete_admin::on_pushButton_clicked()
{
    this ->close();
}


void delete_admin::on_pushButton_2_clicked()
{
    if(QMessageBox::Yes == QMessageBox::question(this, "警告", "您确定要删除吗？"))
    {
        QString admin_id = ui ->lineEdit ->text();
        QSqlQuery mysql;

        mysql.prepare("DELETE FROM admin WHERE `账号` = :number");
        mysql.bindValue(":number", admin_id);

        bool ifdel = mysql.exec();

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


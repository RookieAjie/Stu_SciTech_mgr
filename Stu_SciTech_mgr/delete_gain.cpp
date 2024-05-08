#include "delete_gain.h"
#include "ui_delete_gain.h"
#include "mainwindow.h"
#include <QMessageBox>

delete_gain::delete_gain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::delete_gain)
{
    ui->setupUi(this);

    if(!MainWindow::rowData.empty())
    {
        ui ->lineEdit ->setText(MainWindow::rowData.at(0));
        ui ->lineEdit_2 ->setText(MainWindow::rowData.at(2));

        ui ->lineEdit ->setEnabled(false);
        ui ->lineEdit_2 ->setEnabled(false);

    }
}

delete_gain::~delete_gain()
{
    delete ui;
}

void delete_gain::on_pushButton_clicked()
{
    this ->close();
}


void delete_gain::on_pushButton_2_clicked()
{
    if(QMessageBox::Yes == QMessageBox::question(this, "警告", "您确定要删除吗？"))
    {
        QString group_id = ui ->lineEdit ->text();
        QString achiv_id = ui ->lineEdit_2 ->text();
        QSqlQuery mysql;
        mysql.prepare("DELETE FROM gain WHERE `科研小组组号` = :number and `成果编号` = :num");
        mysql.bindValue(":number", group_id);
        mysql.bindValue(":num", achiv_id);
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


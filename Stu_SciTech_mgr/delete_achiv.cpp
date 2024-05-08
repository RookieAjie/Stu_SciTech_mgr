#include "delete_achiv.h"
#include "ui_delete_achiv.h"
#include "mainwindow.h"
#include <QMessageBox>

delete_achiv::delete_achiv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::delete_achiv)
{
    ui->setupUi(this);

    if(!MainWindow::rowData.empty())
    {
        ui ->lineEdit ->setText(MainWindow::rowData.at(1));
        ui ->lineEdit_2 ->setText(MainWindow::rowData.at(2));
        ui ->lineEdit_3 ->setText(MainWindow::rowData.at(3));
        ui ->textEdit ->setText(MainWindow::rowData.at(4));

        ui ->lineEdit ->setEnabled(false);
        ui ->lineEdit_2 ->setEnabled(false);
        ui ->lineEdit_3 ->setEnabled(false);
        ui ->textEdit ->setEnabled(false);
    }
}

delete_achiv::~delete_achiv()
{
    delete ui;
}

void delete_achiv::on_pushButton_clicked()
{
    this ->close();
}


void delete_achiv::on_pushButton_2_clicked()
{
    if(QMessageBox::Yes == QMessageBox::question(this, "警告", "您确定要删除吗？"))
    {
        QString achi_num = ui ->lineEdit ->text();
        QSqlQuery mysql;
        QSqlQuery mysql2;
        mysql2.prepare("DELETE FROM gain WHERE `成果编号` = :numbe");
        mysql2.bindValue(":numbe", achi_num);
        mysql.prepare("DELETE FROM achievement WHERE `成果编号` = :number");
        mysql.bindValue(":number", achi_num);
        mysql2.exec();
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


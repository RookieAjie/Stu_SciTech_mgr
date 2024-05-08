#include "delete_college.h"
#include "ui_delete_college.h"
#include "mainwindow.h"
#include <QMessageBox>

delete_college::delete_college(QWidget  *parent) :
    QWidget(parent),
    ui(new Ui::delete_college)
{
    ui->setupUi(this);

    if(!MainWindow::rowData.empty())
    {
        ui ->lineEdit_delCollegeNum ->setText(MainWindow::rowData.at(0));
        ui ->lineEdit_2 ->setText(MainWindow::rowData.at(1));
        ui ->textEdit ->setText(MainWindow::rowData.at(2));

        ui ->lineEdit_delCollegeNum ->setEnabled(false);
        ui ->lineEdit_2 ->setEnabled(false);
        ui ->textEdit ->setEnabled(false);

    }
}

delete_college::~delete_college()
{
    delete ui;
}

void delete_college::on_pushButton_clicked()
{
    this ->close();
}


void delete_college::on_pushButton_2_clicked()
{
    if(QMessageBox::Yes == QMessageBox::question(this, "警告", "您确定要删除吗？"))
    {
        QString col_id = ui ->lineEdit_delCollegeNum ->text();
        QSqlQuery mysql;
        QSqlQuery mysql2;

        mysql2.prepare("UPDATE students SET `学院编号` = NULL WHERE `学院编号` =:numb");
        mysql2.bindValue(":numb", col_id);
        mysql2.exec();
        mysql.prepare("DELETE FROM college WHERE `学院编号` = :number");
        mysql.bindValue(":number", col_id);
        bool ifdel = mysql.exec();

        if(ifdel)
        {
            emit collegeDeleted(); // 发射信号
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


#include "update_college.h"
#include "ui_update_college.h"
#include "mainwindow.h"
#include <QMessageBox>

update_college::update_college(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::update_college)
{
    ui->setupUi(this);

    if(!MainWindow::rowData.empty())
    {
        ui ->lineEdit_colID ->setText(MainWindow::rowData.at(0));
        ui ->lineEdit_colName_2 ->setText(MainWindow::rowData.at(1));
        ui ->plainTextEdit ->setPlainText(MainWindow::rowData.at(2));

        ui ->lineEdit_colID ->setEnabled(false);
    }
}

update_college::~update_college()
{
    delete ui;
}

void update_college::on_pushButton_clicked()
{
    this ->close();
}


void update_college::on_pushButton_2_clicked()
{
    QString col_num = ui ->lineEdit_colID->text();
    QString col_name = ui ->lineEdit_colName_2->text();
    QString col_intro = ui ->plainTextEdit->toPlainText();

    QSqlQuery mysql;
    if(col_num != nullptr)
    {
        if(col_name != nullptr && col_intro == nullptr)
        {
            mysql.prepare("UPDATE college SET `学院名称`=:name WHERE `学院编号`=:num;");
            mysql.bindValue(":name", col_name);
            mysql.bindValue(":num", col_num);
        }
        else if(col_name == nullptr && col_intro != nullptr)
        {
            mysql.prepare("UPDATE college SET `学院简介`=:name WHERE `学院编号`=:num;");
            mysql.bindValue(":name", col_intro);
            mysql.bindValue(":num", col_num);
        }
        else if(col_name != nullptr && col_intro != nullptr)
        {
            mysql.prepare("UPDATE college SET `学院名称`=:nam, `学院简介`=:name WHERE `学院编号`=:num;");
            mysql.bindValue(":nam", col_name);
            mysql.bindValue(":name", col_intro);
            mysql.bindValue(":num", col_num);
        }
        else if(col_name == nullptr && col_intro == nullptr)
        {
            QMessageBox::warning(this, "warning", "请输入要修改的学院信息!");
        }
    }
    else
    {
        QMessageBox::warning(this, "warning", "请输入要修改的学院编号!");
    }

    bool ifupdate = mysql.exec();
    if(ifupdate)
    {
        MainWindow w;
        QMessageBox::information(&w, "提示", "修改成功！！");
        qDebug() << "update successfully!!";
        this ->close();
    }
    else
    {
        qDebug() << "update failed!!";
    }

}


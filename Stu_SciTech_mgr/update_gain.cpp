#include "update_gain.h"
#include "ui_update_gain.h"
#include "mainwindow.h"
#include <QMessageBox>
#include "imagedialog.h"
#include <QSqlError>

update_gain::update_gain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::update_gain)
{
    ui->setupUi(this);

    if(!MainWindow::rowData.empty())
    {
        ui ->lineEdit ->setText(MainWindow::rowData.at(0));
        ui ->lineEdit_2 ->setText(MainWindow::rowData.at(2));
        ui ->lineEdit_3 ->setText(MainWindow::rowData.at(1));//小组名称
        ui ->lineEdit_4 ->setText(MainWindow::rowData.at(3));//成果名称
        ui ->comboBox ->setCurrentText(MainWindow::rowData.at(4));

        ui ->lineEdit ->setEnabled(false);
        ui ->lineEdit_2->setEnabled(false);
        ui ->lineEdit_3 ->setEnabled(false);
        ui ->lineEdit_4 ->setEnabled(false);
    }
}

update_gain::~update_gain()
{
    delete ui;
}

void update_gain::on_pushButton_clicked()
{
    this ->close();
}


void update_gain::on_pushButton_2_clicked()
{
    QString Group_id = ui ->lineEdit ->text();
    QString Achi_id = ui ->lineEdit_2 ->text();
    QString result = ui ->comboBox ->currentText();

    QSqlQuery mysql;
    QSqlQuery mysql2;
    if(Group_id != nullptr && Achi_id != nullptr)
    {
        mysql.prepare("UPDATE gain SET `成果编号`=:aid WHERE `科研小组组号`=:gid AND `成果编号`=:aid;");
        mysql2.bindValue(":aid", Achi_id);
        mysql.bindValue(":aid", Achi_id);
        mysql.bindValue(":gid", Group_id);
    }
    else
    {
        QMessageBox::warning(this, "warning", "请输入要修改的成果编号！");
    }

    bool ifupdate = mysql.exec();

    mysql2.prepare("UPDATE gain SET `审批结果`=:res WHERE `科研小组组号`=:gid AND `成果编号`=:aid;");
    mysql2.bindValue(":aid", Achi_id);
    mysql2.bindValue(":gid", Group_id);
    mysql2.bindValue(":res", result);

    bool ifApproval = mysql2.exec();

    if(ifupdate&&ifApproval)
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

void update_gain::on_show_materiall_clicked()
{
    QString group_num = MainWindow::rowData.at(0);
    QString achieve_num = MainWindow::rowData.at(2);
    QSqlQuery query;
    query.prepare("SELECT `相关证明` FROM gain WHERE `科研小组组号` = :num AND `成果编号` = :aid;");
    query.bindValue(":num", group_num);
    query.bindValue(":aid", achieve_num);

    if (query.exec() && query.next()) {
        if(query.value(0).isNull())
        {
            QMessageBox::information(this, "提示", "该绑定申请无证明材料！");
            return;
        }
        QByteArray imageData = query.value(0).toByteArray();

        QImage image;
        image.loadFromData(imageData);
        QPixmap pixmap = QPixmap::fromImage(image);

        // 显示图片对话框
        ImageDialog dialog(pixmap, this);
        dialog.exec(); // 使用exec()来显示模态对话框
    } else {
        qDebug() << "Failed to fetch image data:" << query.lastError().text();
    }
}


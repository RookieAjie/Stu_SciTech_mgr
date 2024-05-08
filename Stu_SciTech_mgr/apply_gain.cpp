#include "apply_gain.h"
#include "ui_apply_gain.h"
#include<QSqlQuery>
#include<QMessageBox>
#include "stumainwindow.h"
#include "mainwindow.h"
#include <QFileDialog>
#include<QBuffer>
#include<QSqlError>
#include<QImageReader>

QByteArray image_Data=NULL;

apply_Gain::apply_Gain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::apply_Gain)
{
    ui->setupUi(this);

    QSqlQuery mysql;
    QSqlQuery mysql_2;
    //连接查询
    mysql.prepare("SELECT * FROM students WHERE `学号`=:number;");
    mysql.bindValue(":number",StuMainwindow::stuAccount);

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

    ui ->lineEdit_id->setText(StuMainwindow::stuAccount);
    ui ->lineEdit_name->setText(mysql.value("姓名").toString());
    ui ->lineEdit_groupid->setText(mysql.value("科研小组号").toString());
    ui ->lineEdit_groupname->setText(mysql_2.value("小组名称").toString());
    ui ->lineEdit_achi_num ->setText(MainWindow::rowData.at(1));
    ui ->lineEdit_achi_name->setText(MainWindow::rowData.at(2));

}

apply_Gain::~apply_Gain()
{
    delete ui;
}

void apply_Gain::on_pushButton_2_clicked()
{
    this->close();
}

void apply_Gain::on_pushButton_3_clicked()
{
    QString Group_id = ui ->lineEdit_groupid ->text();
    QString Achi_id = ui ->lineEdit_achi_num ->text();

    QSqlQuery mysql;
    QSqlQuery mysql_3;
    QSqlQuery mysqlp;

    mysqlp.prepare("SELECT * FROM students WHERE `学号`=:number;");
    mysqlp.bindValue(":number",StuMainwindow::stuAccount);

    qDebug() << "学号为："<< StuMainwindow::stuAccount<< "的学生，科研小组号为："<< mysqlp.value("科研小组号").toInt();
    qDebug() << StuMainwindow::stuAccount;
    if(mysqlp.exec())
    {
        qDebug() << "Myinfo_Select success!";
    }
    else
    {
        qDebug() << "Myinfo_Select failed!";
    }
    mysqlp.next();

    if(mysqlp.value("科研小组号").toInt() == 0)
    {
        QMessageBox::critical(this,"error","请联系管理员加入科研小组！");
        return;
    }

    mysql_3.prepare("SELECT * FROM gain WHERE `科研小组组号` = :nu;");
    mysql_3.bindValue(":nu",mysqlp.value("科研小组号").toInt());
    mysql_3.exec();
    int a[100] = {0};
    int k=0;
    while(mysql_3.next())
    {
        a[k] = mysql_3.value("成果编号").toInt();
        qDebug()<<"a["<<k<<"] = "<< a[k];
        k++;
    }

    k=0;
    if(Group_id != nullptr && Achi_id != nullptr && !ui->lineEdit_achi_name->text().isEmpty())
    {
        int flag=1;
        while(a[k]!=0 && flag==1)
        {
            if(a[k++] == Achi_id.toInt())
            {
                flag =0;
                break;
            }
        }

        if(flag == 0)
        {
            QMessageBox::warning(this, "warning", "请勿重复申请已经绑定的科技成果！");
            return;
        }
        else if(flag ==1 && image_Data.isEmpty())
        {
            mysql.prepare("INSERT INTO Gain(科研小组组号,成果编号,审批结果) VALUE (:gid,:aid,'待审批');");
            mysql.bindValue(":aid", Achi_id);
            mysql.bindValue(":gid", Group_id);

            bool ifupdate = mysql.exec();

            if(ifupdate)
            {
                QMessageBox::information(this, "提示", "申请成功！请等待管理员审核！");
                qDebug() << "update successfully!!";
                this ->close();
            }
            else
            {
                qDebug() << "申请失败!!";
            }
        }
        else if(flag ==1 && !image_Data.isEmpty())
        {
            mysql.prepare("INSERT INTO Gain(科研小组组号,成果编号,审批结果,相关证明) VALUE (:gid,:aid,'待审批',:image);");
            mysql.bindValue(":aid", Achi_id);
            mysql.bindValue(":gid", Group_id);
            mysql.bindValue(":image", image_Data);

            bool ifupdate = mysql.exec();

            if(ifupdate)
            {
                QMessageBox::information(this, tr("Success"), tr("相关证明上传成功!"));
                QMessageBox::information(this, "Success", "申请成功！请等待管理员审核！");
                qDebug() << "update successfully!!";
                this ->close();
            }
            else
            {
                qDebug() << "申请失败!!";
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "warning", "请输入要正确的成果编号！");
    }
}


void apply_Gain::on_pushButton_4_clicked()
{
    // 打开文件对话框选择图片
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Select Image"), "", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));

    if (!imagePath.isEmpty()) {
        // 读取图片文件为QImage
        QImage image;
        QImageReader reader(imagePath);
        if (!reader.read(&image)) { // 使用read()的返回值来判断是否成功
            QMessageBox::warning(this, tr("Error"), tr("Cannot load image: %1").arg(reader.errorString()));
            return;
        }

        // 将QImage转换为QByteArray
        QBuffer buffer(&image_Data);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG"); // 这里以PNG格式保存，可根据需要调整
    }
}


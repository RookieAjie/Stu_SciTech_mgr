#include "apply_achievement.h"
#include "ui_apply_achievement.h"
#include<QSqlQuery>
#include<QMessageBox>
#include<QFileDialog>
#include<QBuffer>
#include<QSqlError>
#include<QImageReader>

QByteArray imageData=NULL;

apply_Achievement::apply_Achievement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::apply_Achievement)
{
    ui->setupUi(this);
}

apply_Achievement::~apply_Achievement()
{
    delete ui;
}

void apply_Achievement::on_pushButton_2_clicked()
{
    QDate q = ui ->dateEdit ->date();
    QString name = ui ->lineEdit ->text();
    QString time = q.toString("yyyy-MM-dd");//Qdate转为Qstring
    QString intro = ui ->plainTextEdit ->toPlainText();

    QSqlQuery mysql;
    if(name != nullptr && time != nullptr && intro != nullptr && imageData.isEmpty())
    {
        mysql.prepare("INSERT INTO Achievement(成果名称,时间,简介,审批意见) VALUE (:nam,:tim,:introduction,'待审批');");

        mysql.bindValue(":nam",name);
        mysql.bindValue(":tim",time);
        mysql.bindValue(":introduction",intro);

        bool add_success = mysql.exec();
        if(add_success)
        {
            qDebug() << "add successfully!!";

            QMessageBox::information(this,"tip", "申请成功！请等待管理员审批！");
            this ->close();
        }
    }
    else if(name != nullptr && time != nullptr && intro != nullptr && !imageData.isEmpty())
    {
        mysql.prepare("INSERT INTO Achievement(成果名称,时间,简介,审批意见,证明材料) VALUE (:nam,:tim,:introduction,'待审批',:image);");

        mysql.bindValue(":nam",name);
        mysql.bindValue(":tim",time);
        mysql.bindValue(":introduction",intro);
        mysql.bindValue(":image",imageData);

        bool add_success = mysql.exec();
        if(add_success)
        {
            QMessageBox::information(this, tr("Success"), tr("证明材料上传成功!"));
            QMessageBox::information(this,"Success", "申请成功！请等待管理员审批！");
            this ->close();
        }
    }
    else
    {
        QMessageBox::warning(this, "warning", "请输入要申请添加的成果信息！！");
    }
}


void apply_Achievement::on_pushButton_clicked()
{
    this->close();
}


void apply_Achievement::on_add_materials_clicked()
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
        QBuffer buffer(&imageData);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG"); // 这里以PNG格式保存，可根据需要调整
    }
}


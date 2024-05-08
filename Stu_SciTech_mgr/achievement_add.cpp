#include "achievement_add.h"
#include "ui_achievement_add.h"

achievement_add::achievement_add(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::achievement_add)
{
    ui->setupUi(this);
}

achievement_add::~achievement_add()
{
    delete ui;
}

void achievement_add::on_return_btn_clicked()
{
    this ->close();
}


void achievement_add::on_achiv_addbtn_clicked()
{
    QDate q = ui ->dateEdit ->date();
    QString name = ui ->lineEdit ->text();
    QString time = q.toString("yyyy-MM-dd");//Qdate转为Qstring
    QString intro = ui ->plainTextEdit ->toPlainText();

    QSqlQuery mysql;
    if(name != nullptr && time != nullptr && intro != nullptr)
    {
        mysql.prepare("INSERT INTO Achievement(成果名称,时间,简介,审批意见) VALUE (:nam,:tim,:introduction,'通过');");

        mysql.bindValue(":nam",name);
        mysql.bindValue(":tim",time);
        mysql.bindValue(":introduction",intro);
    }
    else
    {
        QMessageBox::warning(this, "warning", "请输入要添加的成果信息！！");
    }

    bool add_success = mysql.exec();
    if(add_success)
    {
        qDebug() << "add successfully!!";

        QMessageBox::information(this,"tip", "添加成功！！");
        this ->close();
    }
}

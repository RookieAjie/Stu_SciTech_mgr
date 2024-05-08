#include "achievement_update.h"
#include "ui_achievement_update.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "imagedialog.h"
#include <QSqlError>

achievement_update::achievement_update(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::achievement_update)
{
    ui->setupUi(this);

    if(!MainWindow::rowData.empty())
    {
        QString q = MainWindow::rowData.at(3);
        qDebug() << q;
        QDate date=QDate::fromString(q,"yyyy-M-d");
        qDebug() << date.toString();

        ui ->lineEdit ->setText(MainWindow::rowData.at(1));
        ui ->lineEdit_2 ->setText(MainWindow::rowData.at(2));
        ui ->dateEdit->setDate(date);
        ui ->plainTextEdit ->setPlainText(MainWindow::rowData.at(4));
        ui ->comboBox->setCurrentText(MainWindow::rowData.at(0));

        ui ->lineEdit ->setEnabled(false);
    }
}

achievement_update::~achievement_update()
{
    delete ui;
}

void achievement_update::on_return_btn_clicked()
{
    this ->close();
}


void achievement_update::on_updaAchi_btn_clicked()
{
    QDate q = ui ->dateEdit->date();
    QString achi_num = ui ->lineEdit ->text();
    QString achi_nam = ui ->lineEdit_2 ->text();
    QString achi_intro = ui ->plainTextEdit ->toPlainText();
    QString achi_time = q.toString("yyyy-MM-dd");
    QString result = ui->comboBox->currentText();

    QSqlQuery mysql;
    if(achi_num != nullptr)
    {
        if(achi_nam != nullptr && achi_intro == nullptr && achi_time == nullptr)
        {
            mysql.prepare("UPDATE achievement SET `成果名称`=:name,`审批意见`=:res WHERE `成果编号`=:num;");
            mysql.bindValue(":name", achi_nam);
            mysql.bindValue(":res", result);
            mysql.bindValue(":num", achi_num);
        }
        else if(achi_nam == nullptr && achi_intro != nullptr && achi_time == nullptr)
        {
            mysql.prepare("UPDATE achievement SET `简介`=:name,`审批意见`=:res WHERE `成果编号`=:num;");
            mysql.bindValue(":name", achi_intro);
            mysql.bindValue(":res", result);
            mysql.bindValue(":num", achi_num);
        }
        else if(achi_nam == nullptr && achi_intro == nullptr && achi_time != nullptr)
        {
            mysql.prepare("UPDATE achievement SET `时间`=:name,`审批意见`=:res WHERE `成果编号`=:num;");
            mysql.bindValue(":name", achi_time);
            mysql.bindValue(":res", result);
            mysql.bindValue(":num", achi_num);
        }
        else if(achi_nam != nullptr && achi_intro != nullptr && achi_time == nullptr)
        {
            mysql.prepare("UPDATE achievement SET `成果名称`=:name,`简介`=:nam,`审批意见`=:res WHERE `成果编号`=:num;");
//            mysql.prepare("UPDATE achievement SET `简介`=:nam WHERE `成果编号`=:num;");
            mysql.bindValue(":name", achi_nam);
            mysql.bindValue(":nam", achi_intro);
            mysql.bindValue(":res", result);
            mysql.bindValue(":num", achi_num);
        }
        else if(achi_nam != nullptr && achi_intro == nullptr && achi_time != nullptr)
        {
            mysql.prepare("UPDATE achievement SET `成果名称`=:name,`时间`=:nam,`审批意见`=:res WHERE `成果编号`=:num;");
 //           mysql.prepare("UPDATE achievement SET `时间`=:nam WHERE `成果编号`=:num;");
            mysql.bindValue(":name", achi_nam);
            mysql.bindValue(":nam", achi_time);
            mysql.bindValue(":res", result);
            mysql.bindValue(":num", achi_num);
        }
        else if(achi_nam == nullptr && achi_intro != nullptr && achi_time != nullptr)
        {
            mysql.prepare("UPDATE achievement SET `简介`=:name,`时间`=:nam,`审批意见`=:res WHERE `成果编号`=:num;");
            mysql.bindValue(":name", achi_intro);
            mysql.bindValue(":nam", achi_time);
            mysql.bindValue(":res", result);
            mysql.bindValue(":num", achi_num);
        }
        else if(achi_nam != nullptr && achi_intro != nullptr && achi_time != nullptr)
        {
            mysql.prepare("UPDATE achievement SET `成果名称`=:name, `简介`=:nname, `时间`=:nnam,`审批意见`=:res WHERE `成果编号`=:num;");
            mysql.bindValue(":name", achi_nam);
            mysql.bindValue(":nname", achi_intro);
            mysql.bindValue(":nnam", achi_time);
            mysql.bindValue(":res", result);
            mysql.bindValue(":num", achi_num);
        }
        else
        {
            QMessageBox::warning(this,"warning","请输入要修改的信息！");
        }

    }
    else if(achi_num == nullptr)
    {
        QMessageBox::warning(this, "warning", "请输入要修改的成果编号！");
    }

    bool ifupdate = mysql.exec();
    //ui ->lineEdit_num ->clear();
    if(ifupdate)
    {
        QMessageBox::information(this, "提示", "修改成功！！");
        qDebug() << "update successfully!!";
    }
    else
    {
        qDebug() << "update failed!!";
    }

    this ->close();
}


void achievement_update::on_show_material_clicked()
{
    QString achieve_num = MainWindow::rowData.at(1);
    QSqlQuery query;
    query.prepare("SELECT `证明材料` FROM achievement WHERE `成果编号` =:num;");
    query.bindValue(":num", achieve_num);
    if (query.exec() && query.next()) {
        if(query.value(0).isNull())
        {
            QMessageBox::information(this, "提示", "该成果无证明材料！");
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


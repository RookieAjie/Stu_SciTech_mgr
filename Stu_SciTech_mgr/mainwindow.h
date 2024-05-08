#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "page_login.h"

#include <QApplication>
#include <QSqlRecord>
#include <QSqlField>
#include <QFile>
#include <QTextStream>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static QString AdminAccount;
    static QStringList rowData;

    void setInfo_table();
    void setInfo_table2();
    void setInfo_table3();
    void setInfo_table4();
    void setInfo_table5();
    void setInfo_table6();
    void setInfo_table7();
    void setInfo_table8();
    void setInfo_table9();



    void getInfo_Database();
    void getInfo_stu();
    void getInfo_group();
    void getInfo_achievement();
    void getInfo_Gain();
    void getInfo_admin();
    void getInfo_college();
    void ExportTaskInformation();
    void getInfo_GainGroup();
    void getInfo_GainAchiv();


    QString getStucount();
    QString getGrpCount();
    QString getAchivCount();
    QString getCollegeCount();
    QString getMinAge();
    QStringList getMinAgeStu_name();
    QString getadminName();

private slots:
    void on_btn_exit_clicked();


    void on_add_btn_clicked();



    void on_search_btn_clicked();

    void on_pushButton_clicked();

    void on_delete_btn_clicked();

    void on_update_btn_clicked();

    void on_pushButton_2_clicked();

    void on_addgroup_btn_clicked();

    void on_delGroup_btn_clicked();

    void on_updategroup_btn_clicked();

    void on_achivSearch_btn_clicked();

    void on_Addachiv_btn_2_clicked();

    void on_updateAchiv_btn_clicked();

    void on_del_btn_clicked();

    void on_SearchForGain_btn_clicked();

    void on_addGain_btn_clicked();

    void on_GainUpdate_btn_clicked();

    void on_delet_btn_clicked();

    void on_search_btn_2_clicked();

    void on_add_btn_2_clicked();

    void on_change_btn_clicked();

    void on_del_btn_2_clicked();

    void on_pushButton_3_clicked();


    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_outToExcel_btn_clicked();


    void on_outToTxt_btn_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void onCollegeDeleted();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

private:
    Ui::MainWindow *ui;
//    page_login m_dlgLogin;

};
#endif // MAINWINDOW_H

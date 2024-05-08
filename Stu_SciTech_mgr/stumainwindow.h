#ifndef STUMAINWINDOW_H
#define STUMAINWINDOW_H
#include "page_login.h"


#include <QWidget>

namespace Ui {
class StuMainwindow;
}

class StuMainwindow : public QWidget
{
    Q_OBJECT

public:
    explicit StuMainwindow(QWidget *parent = nullptr);
    ~StuMainwindow();

    static QString stuAccount;

    void setStuInfo_table();
    void setStuInfo_table2();
    void setStuInfo_table3();
    void setStuInfo_table4();
    void setStuInfo_table5();

    void getStuInfo_database();
    void getInfoGroup();
    void getInfoAchiv();
    void getMyInfo();
    void getInfoCollege();

    QString getName();
    QString getStudentCount();
    QString getCollegeCounts();

private slots:
    void on_exit_btn_clicked();

    void on_sql_btnqiaotao_clicked();

    void on_search_btn_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();


    void on_pushButton_5_clicked();


    void on_btn_applyForAchi_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::StuMainwindow *ui;
};

#endif // STUMAINWINDOW_H

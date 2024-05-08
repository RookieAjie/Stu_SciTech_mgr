#ifndef DELETE_STU_H
#define DELETE_STU_H

#include <QWidget>

namespace Ui {
class delete_Stu;
}

class delete_Stu : public QWidget
{
    Q_OBJECT

public:
    explicit delete_Stu(QWidget *parent = nullptr);
    ~delete_Stu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::delete_Stu *ui;
};

#endif // DELETE_STU_H

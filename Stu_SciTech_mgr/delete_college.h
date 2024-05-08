#ifndef DELETE_COLLEGE_H
#define DELETE_COLLEGE_H

#include <QWidget>

namespace Ui {
class delete_college;
}

class delete_college : public QWidget
{
    Q_OBJECT

public:
    explicit delete_college(QWidget *parent = nullptr);
    ~delete_college();

signals:
    void collegeDeleted();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::delete_college *ui;
};

#endif // DELETE_COLLEGE_H

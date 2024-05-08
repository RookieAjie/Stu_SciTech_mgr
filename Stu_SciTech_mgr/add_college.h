#ifndef ADD_COLLEGE_H
#define ADD_COLLEGE_H

#include <QWidget>

namespace Ui {
class add_college;
}

class add_college : public QWidget
{
    Q_OBJECT

public:
    explicit add_college(QWidget *parent = nullptr);
    ~add_college();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::add_college *ui;
};

#endif // ADD_COLLEGE_H

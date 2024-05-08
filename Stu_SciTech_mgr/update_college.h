#ifndef UPDATE_COLLEGE_H
#define UPDATE_COLLEGE_H

#include <QWidget>

namespace Ui {
class update_college;
}

class update_college : public QWidget
{
    Q_OBJECT

public:
    explicit update_college(QWidget *parent = nullptr);
    ~update_college();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::update_college *ui;
};

#endif // UPDATE_COLLEGE_H

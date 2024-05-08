#ifndef ADD_INFO_H
#define ADD_INFO_H

#include <QWidget>

namespace Ui {
class add_info;
}

class add_info : public QWidget
{
    Q_OBJECT

public:
    explicit add_info(QWidget *parent = nullptr);
    ~add_info();

private slots:
    void on_return_btn_clicked();

    void on_moveall_btn_clicked();

    void on_addInfo_btn_clicked();

private:
    Ui::add_info *ui;
};

#endif // ADD_INFO_H

#ifndef UPDATE_ADMIN_H
#define UPDATE_ADMIN_H

#include <QWidget>

namespace Ui {
class update_admin;
}

class update_admin : public QWidget
{
    Q_OBJECT

public:
    explicit update_admin(QWidget *parent = nullptr);
    ~update_admin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::update_admin *ui;
};

#endif // UPDATE_ADMIN_H

#ifndef ADD_ADMIN_H
#define ADD_ADMIN_H

#include <QWidget>

namespace Ui {
class add_admin;
}

class add_admin : public QWidget
{
    Q_OBJECT

public:
    explicit add_admin(QWidget *parent = nullptr);
    ~add_admin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::add_admin *ui;
};

#endif // ADD_ADMIN_H

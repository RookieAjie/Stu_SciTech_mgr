#ifndef DELETE_ADMIN_H
#define DELETE_ADMIN_H

#include <QWidget>

namespace Ui {
class delete_admin;
}

class delete_admin : public QWidget
{
    Q_OBJECT

public:
    explicit delete_admin(QWidget *parent = nullptr);
    ~delete_admin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::delete_admin *ui;
};

#endif // DELETE_ADMIN_H

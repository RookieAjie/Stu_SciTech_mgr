#ifndef DELETE_GROUP_H
#define DELETE_GROUP_H

#include <QWidget>

namespace Ui {
class delete_group;
}

class delete_group : public QWidget
{
    Q_OBJECT

public:
    explicit delete_group(QWidget *parent = nullptr);
    ~delete_group();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::delete_group *ui;
};

#endif // DELETE_GROUP_H

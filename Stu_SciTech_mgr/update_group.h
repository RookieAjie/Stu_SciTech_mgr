#ifndef UPDATE_GROUP_H
#define UPDATE_GROUP_H

#include <QWidget>

namespace Ui {
class update_group;
}

class update_group : public QWidget
{
    Q_OBJECT

public:
    explicit update_group(QWidget *parent = nullptr);
    ~update_group();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::update_group *ui;
};

#endif // UPDATE_GROUP_H

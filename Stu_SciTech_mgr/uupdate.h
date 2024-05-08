#ifndef UUPDATE_H
#define UUPDATE_H

#include <QWidget>

namespace Ui {
class update;
}

class update : public QWidget
{
    Q_OBJECT

public:
    explicit update(QWidget *parent = nullptr);
    ~update();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::update *ui;
};

#endif // UUPDATE_H

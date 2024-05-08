#ifndef UPDATE_GAIN_H
#define UPDATE_GAIN_H

#include <QWidget>

namespace Ui {
class update_gain;
}

class update_gain : public QWidget
{
    Q_OBJECT

public:
    explicit update_gain(QWidget *parent = nullptr);
    ~update_gain();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_show_materiall_clicked();

private:
    Ui::update_gain *ui;
};

#endif // UPDATE_GAIN_H

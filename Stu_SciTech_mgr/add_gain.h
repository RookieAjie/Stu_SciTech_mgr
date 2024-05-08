#ifndef ADD_GAIN_H
#define ADD_GAIN_H

#include <QWidget>

namespace Ui {
class add_gain;
}

class add_gain : public QWidget
{
    Q_OBJECT

public:
    explicit add_gain(QWidget *parent = nullptr);
    ~add_gain();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::add_gain *ui;
};

#endif // ADD_GAIN_H

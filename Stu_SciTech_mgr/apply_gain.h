#ifndef APPLY_GAIN_H
#define APPLY_GAIN_H

#include <QWidget>

namespace Ui {
class apply_Gain;
}

class apply_Gain : public QWidget
{
    Q_OBJECT

public:
    explicit apply_Gain(QWidget *parent = nullptr);
    ~apply_Gain();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::apply_Gain *ui;
};

#endif // APPLY_GAIN_H

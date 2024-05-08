#ifndef DELETE_GAIN_H
#define DELETE_GAIN_H

#include <QWidget>

namespace Ui {
class delete_gain;
}

class delete_gain : public QWidget
{
    Q_OBJECT

public:
    explicit delete_gain(QWidget *parent = nullptr);
    ~delete_gain();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::delete_gain *ui;
};

#endif // DELETE_GAIN_H

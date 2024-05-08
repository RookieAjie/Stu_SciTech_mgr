#ifndef DELETE_ACHIV_H
#define DELETE_ACHIV_H

#include <QWidget>

namespace Ui {
class delete_achiv;
}

class delete_achiv : public QWidget
{
    Q_OBJECT

public:
    explicit delete_achiv(QWidget *parent = nullptr);
    ~delete_achiv();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::delete_achiv *ui;
};

#endif // DELETE_ACHIV_H

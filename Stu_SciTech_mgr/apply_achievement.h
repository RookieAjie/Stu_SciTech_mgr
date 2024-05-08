#ifndef APPLY_ACHIEVEMENT_H
#define APPLY_ACHIEVEMENT_H

#include <QWidget>

namespace Ui {
class apply_Achievement;
}

class apply_Achievement : public QWidget
{
    Q_OBJECT

public:
    explicit apply_Achievement(QWidget *parent = nullptr);
    ~apply_Achievement();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_add_materials_clicked();

private:
    Ui::apply_Achievement *ui;
};

#endif // APPLY_ACHIEVEMENT_H

#ifndef ACHIEVEMENT_ADD_H
#define ACHIEVEMENT_ADD_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class achievement_add;
}

class achievement_add : public QWidget
{
    Q_OBJECT

public:
    explicit achievement_add(QWidget *parent = nullptr);
    ~achievement_add();

private slots:
    void on_return_btn_clicked();

    void on_achiv_addbtn_clicked();


private:
    Ui::achievement_add *ui;
};

#endif // ACHIEVEMENT_ADD_H

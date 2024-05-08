#ifndef ACHIEVEMENT_UPDATE_H
#define ACHIEVEMENT_UPDATE_H

#include <QWidget>

namespace Ui {
class achievement_update;
}

class achievement_update : public QWidget
{
    Q_OBJECT

public:
    explicit achievement_update(QWidget *parent = nullptr);
    ~achievement_update();

private slots:
    void on_return_btn_clicked();

    void on_updaAchi_btn_clicked();

    void on_show_material_clicked();

private:
    Ui::achievement_update *ui;
};

#endif // ACHIEVEMENT_UPDATE_H

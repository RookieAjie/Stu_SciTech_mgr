#ifndef IMAGEDIALOG_H
#define IMAGEDIALOG_H


#include <QDialog>
#include <QLabel>
#include <QPixmap>

class ImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageDialog(const QPixmap &pixmap, QWidget *parent = nullptr);
};

#endif // IMAGEDIALOG_H

#include "imagedialog.h"
#include <QLayout>
#include <QScrollArea> // 添加对QScrollArea的支持

ImageDialog::ImageDialog(const QPixmap &pixmap, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("证明材料"));
    setModal(true);
    setFixedSize(700, 500); // 保持对话框的固定大小

    QLabel *imageLabel = new QLabel(this);
    imageLabel->setPixmap(pixmap);
    imageLabel->setAlignment(Qt::AlignCenter);

    // 使用QScrollArea来包裹QLabel，这样即使图片大于对话框也能通过滚动查看
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true); // 允许内部widget调整大小
    scrollArea->setWidget(imageLabel);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setStyleSheet("background-color: transparent;"); // 可选，透明背景

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(scrollArea);
    setLayout(layout);
}

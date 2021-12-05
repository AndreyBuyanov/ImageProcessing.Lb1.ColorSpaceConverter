#include "QCanvas.hpp"

#include <QPainter>

QCanvas::QCanvas(QWidget *parent):
    QWidget(parent),
    m_Image(nullptr)
{
}

void QCanvas::changeImage(
    const QImage *image)
{
    std::unique_lock<decltype(m_LockImage)> lock(m_LockImage);
    m_Image = image;
    resize(m_Image->size());
    setMinimumSize(m_Image->size());
}

void QCanvas::paintEvent(
    QPaintEvent *)
{
    std::unique_lock<decltype(m_LockImage)> lock(m_LockImage);
    if (m_Image) {
        QPainter painter(this);
        painter.drawImage(0, 0, *m_Image);
    }
}

#include "QScrollableCanvas.hpp"

QScrollableCanvas::QScrollableCanvas(
    QWidget *parent)
    : QScrollArea(parent)
    , m_Canvas(new QCanvas())
{
}

void QScrollableCanvas::onChangeImage(
    const QImage *image)
{
    setWidget(nullptr);
    m_Canvas->changeImage(image);
    setWidget(m_Canvas.get());
    emit imageChanged();
}


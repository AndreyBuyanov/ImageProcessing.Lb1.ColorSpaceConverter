#pragma once

#include <QScrollArea>

#include <memory>

#include "QCanvas.hpp"

class QScrollableCanvas : public QScrollArea
{
    Q_OBJECT
public:
    explicit QScrollableCanvas(
        QWidget* parent = nullptr);
signals:
    void imageChanged();
public slots:
    void onChangeImage(
        const QImage* image);
private:
    std::unique_ptr<QCanvas> m_Canvas;
};


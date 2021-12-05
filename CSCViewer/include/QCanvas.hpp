#pragma once

#include <QWidget>

#include <mutex>

class QCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit QCanvas(
        QWidget* parent = nullptr);
    void changeImage(
        const QImage* image);
private:
    const QImage *m_Image;
    std::mutex m_LockImage;

    void paintEvent(
        QPaintEvent *) override;
};


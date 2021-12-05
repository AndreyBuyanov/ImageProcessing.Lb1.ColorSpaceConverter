#pragma once

#include <QObject>
#include <QImage>

#include "IConverter.hpp"

enum class ColorSpaceType
{
    YUV_BT601 = 0,
    YUV_BT709,
    HSV
};

class Manager
    : public QObject
{
    Q_OBJECT
public:
    explicit Manager(
        QObject* parent = nullptr);

    bool loadImage(
        const QString& fileName);
    bool saveResult(
        const QString& fileName);
    bool saveChannel1(
        const QString& fileName);
    bool saveChannel2(
        const QString& fileName);
    bool saveChannel3(
        const QString& fileName);
signals:
    void inputImageChanged(
        const QImage* image);
    void channel1ImageChanged(
        const QImage* image);
    void channel2ImageChanged(
        const QImage* image);
    void channel3ImageChanged(
        const QImage* image);
    void outputImageChanged(
        const QImage* image);
public slots:
    void onChangeChannel1Value(
        const int value);
    void onChangeChannel2Value(
        const int value);
    void onChangeChannel3Value(
        const int value);
    void onChangeColorSpaceType(
        const int type);
    void onReset();
private:
    void initImage();
    void changeChannel1(
        const int dValue);
    void changeChannel2(
        const int dValue);
    void changeChannel3(
        const int dValue);
    void updateChannel1();
    void updateChannel2();
    void updateChannel3();
    void updateOutput();

    QImage m_InputImage;
    QImage m_Channel1Image;
    QImage m_Channel2Image;
    QImage m_Channel3Image;
    QImage m_OutputImage;
    ColorSpaceType m_type = static_cast<ColorSpaceType>(0);
    std::unique_ptr<CSCEngine::IConverter> m_converter;
    std::unique_ptr<CSCEngine::YUVImage> m_YUVImage;
    std::unique_ptr<CSCEngine::HSVImage> m_HSVImage;
    bool m_initialized = false;
};

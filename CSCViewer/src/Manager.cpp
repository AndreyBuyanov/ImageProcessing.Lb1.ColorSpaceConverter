#include "Manager.hpp"

#include "Helper.hpp"

static CSCEngine::RGBImageView toView(
    QImage& image)
{
    return CSCEngine::RGBImageView {
        static_cast<std::uint8_t*>(image.bits()),
        static_cast<std::size_t>(image.width()),
        static_cast<std::size_t>(image.height())
    };
}

void Manager::initImage()
{
    if (ColorSpaceType::YUV_BT601 == m_type) {
        m_YUVImage = m_converter->Convert(
            toView(m_InputImage), CSCEngine::YUVType::YUV_BT601);
    }
    else if (ColorSpaceType::YUV_BT709 == m_type) {
        m_YUVImage = m_converter->Convert(
            toView(m_InputImage), CSCEngine::YUVType::YUV_BT709);
    }
    else if (ColorSpaceType::HSV == m_type) {
        m_HSVImage = m_converter->Convert(
            toView(m_InputImage));
    }

    updateChannel1();
    updateChannel2();
    updateChannel3();
    updateOutput();
}

void Manager::changeChannel1(
    const int dValue)
{
    if (ColorSpaceType::YUV_BT601 == m_type
        || ColorSpaceType::YUV_BT709 == m_type)
    {
        CSCEngine::Helper::ChangeY(m_YUVImage, dValue);
    } else if (ColorSpaceType::HSV == m_type) {
        CSCEngine::Helper::ChangeH(m_HSVImage, dValue);
    }
    updateChannel1();
}

void Manager::changeChannel2(
    const int dValue)
{
    if (ColorSpaceType::YUV_BT601 == m_type
        || ColorSpaceType::YUV_BT709 == m_type)
    {
        CSCEngine::Helper::ChangeU(m_YUVImage, dValue);
    } else if (ColorSpaceType::HSV == m_type) {
        CSCEngine::Helper::ChangeS(m_HSVImage, dValue);
    }
    updateChannel2();
}

void Manager::changeChannel3(
    const int dValue)
{
    if (ColorSpaceType::YUV_BT601 == m_type
        || ColorSpaceType::YUV_BT709 == m_type)
    {
        CSCEngine::Helper::ChangeV(m_YUVImage, dValue);
    } else if (ColorSpaceType::HSV == m_type) {
        CSCEngine::Helper::ChangeV(m_HSVImage, dValue);
    }
    updateChannel3();
}

void Manager::updateChannel1()
{
    if (ColorSpaceType::YUV_BT601 == m_type
        || ColorSpaceType::YUV_BT709 == m_type)
    {
        CSCEngine::Helper::Y2RGB(
            m_YUVImage,
            toView(m_Channel1Image));
    } else if (ColorSpaceType::HSV == m_type) {
        CSCEngine::Helper::H2RGB(
            m_HSVImage,
            toView(m_Channel1Image));
    }
    emit channel1ImageChanged(&m_Channel1Image);
}

void Manager::updateChannel2()
{
    if (ColorSpaceType::YUV_BT601 == m_type
        || ColorSpaceType::YUV_BT709 == m_type)
    {
        CSCEngine::Helper::U2RGB(
            m_YUVImage,
            toView(m_Channel2Image));
    } else if (ColorSpaceType::HSV == m_type) {
        CSCEngine::Helper::S2RGB(
            m_HSVImage,
            toView(m_Channel2Image));
    }
    emit channel2ImageChanged(&m_Channel2Image);
}

void Manager::updateChannel3()
{
    if (ColorSpaceType::YUV_BT601 == m_type
        || ColorSpaceType::YUV_BT709 == m_type)
    {
        CSCEngine::Helper::V2RGB(
            m_YUVImage,
            toView(m_Channel3Image));
    } else if (ColorSpaceType::HSV == m_type) {
        CSCEngine::Helper::V2RGB(
            m_HSVImage,
            toView(m_Channel3Image));
    }
    emit channel3ImageChanged(&m_Channel3Image);
}

void Manager::updateOutput()
{
    if (ColorSpaceType::YUV_BT601 == m_type) {
        m_converter->Convert(
            toView(m_OutputImage),
            m_YUVImage,
            CSCEngine::YUVType::YUV_BT601);
    } else if (ColorSpaceType::YUV_BT709 == m_type) {
        m_converter->Convert(
            toView(m_OutputImage),
            m_YUVImage,
            CSCEngine::YUVType::YUV_BT709);
    } else if (ColorSpaceType::HSV == m_type) {
        m_converter->Convert(
            toView(m_OutputImage),
            m_HSVImage);
    }
    emit outputImageChanged(&m_OutputImage);
}

Manager::Manager(
    QObject* parent)
    : QObject(parent)
    , m_converter(CSCEngine::CreateConverter())
{
}

bool Manager::loadImage(
    const QString& fileName)
{
    QImage image;
    if (!image.load(fileName)) {
        return false;
    }
    // check format
    image = image.convertToFormat(QImage::Format_RGB888);
    m_initialized = true;
    m_InputImage = std::move(image);
    m_Channel1Image = QImage(m_InputImage.size(), m_InputImage.format());
    m_Channel2Image = QImage(m_InputImage.size(), m_InputImage.format());
    m_Channel3Image = QImage(m_InputImage.size(), m_InputImage.format());
    m_OutputImage = QImage(m_InputImage.size(), m_InputImage.format());

    emit inputImageChanged(&m_InputImage);

    initImage();

    return true;
}

bool Manager::saveResult(
    const QString& fileName)
{
    if (!m_initialized) {
        return false;
    }
    return m_OutputImage.save(fileName);
}

bool Manager::saveChannel1(
    const QString& fileName)
{
    if (!m_initialized) {
        return false;
    }
    return m_Channel1Image.save(fileName);
}

bool Manager::saveChannel2(
    const QString& fileName)
{
    if (!m_initialized) {
        return false;
    }
    return m_Channel2Image.save(fileName);
}

bool Manager::saveChannel3(
    const QString& fileName)
{
    if (!m_initialized) {
        return false;
    }
    return m_Channel3Image.save(fileName);
}

void Manager::onChangeChannel1Value(
    int value)
{
    if (!m_initialized) {
        return;
    }
    changeChannel1(value);
    updateOutput();
}

void Manager::onChangeChannel2Value(
    int value)
{
    if (!m_initialized) {
        return;
    }
    changeChannel2(value);
    updateOutput();
}

void Manager::onChangeChannel3Value(
    int value)
{
    if (!m_initialized) {
        return;
    }
    changeChannel3(value);
    updateOutput();
}

void Manager::onChangeColorSpaceType(
    int type)
{
    m_type = static_cast<ColorSpaceType>(type);
    if (!m_initialized) {
        return;
    }
    initImage();
}

void Manager::onReset()
{
    if (!m_initialized) {
        return;
    }
    initImage();
}

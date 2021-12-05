#pragma once

#include "IConverter.hpp"

namespace CSCEngine
{

class Converter
    : public IConverter
{
public:
    Converter() = default;
    virtual ~Converter() = default;

    std::unique_ptr<YUVImage> Convert(
        const RGBImageView& image,
        const YUVType imageType) const override;

    std::unique_ptr<HSVImage> Convert(
        const RGBImageView& image) const override;

    void Convert(
        RGBImageView outputImage,
        const std::unique_ptr<YUVImage>& inputImage,
        const YUVType imageType) const override;

    void Convert(
        RGBImageView outputImage,
        const std::unique_ptr<HSVImage>& inputImage) const override;
};

}

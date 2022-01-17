#pragma once

#include "IConverter.hpp"

namespace CSCEngine
{

class Converter
    : public IConverter
{
public:
    Converter() = default;
    ~Converter() override = default;

    [[nodiscard]] std::unique_ptr<YUVImage> Convert(
        const RGBImageView& image,
        YUVType imageType) const override;

    [[nodiscard]] std::unique_ptr<HSVImage> Convert(
        const RGBImageView& image) const override;

    void Convert(
        RGBImageView outputImage,
        const std::unique_ptr<YUVImage>& inputImage,
        YUVType imageType) const override;

    void Convert(
        RGBImageView outputImage,
        const std::unique_ptr<HSVImage>& inputImage) const override;
};

}

#pragma once

#include <memory>

#include "Types.hpp"
#include "Image.hpp"

namespace CSCEngine
{

class IConverter
{
public:
    virtual ~IConverter() = default;

    virtual std::unique_ptr<YUVImage> Convert(
        const RGBImageView& image,
        const YUVType imageType) const = 0;

    virtual std::unique_ptr<HSVImage> Convert(
        const RGBImageView& image) const = 0;

    virtual void Convert(
        RGBImageView outputImage,
        const std::unique_ptr<YUVImage>& inputImage,
        const YUVType imageType) const = 0;

    virtual void Convert(
        RGBImageView outputImage,
        const std::unique_ptr<HSVImage>& inputImage) const = 0;
};

std::unique_ptr<IConverter> CreateConverter();

}

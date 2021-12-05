#include "Converter.hpp"

#include <cassert>

#include <xtensor/xarray.hpp>
#include <xtensor/xadapt.hpp>
#include <xtensor/xview.hpp>
#include <cmath>

namespace CSCEngine
{

using namespace xt::placeholders;

static void RGB2HSV(
    const float r,
    const float g,
    const float b,
    float& h,
    float& s,
    float& v)
{
    float cMax = std::max(std::max(r, g), b);
    float cMin = std::min(std::min(r, g), b);
    float delta = cMax - cMin;

    if(delta > 0.0f) {
        if(cMax == r) {
            h = 60.0f * (static_cast<float>(std::fmod(((g - b) / delta), 6)));
        } else if(cMax == g) {
            h = 60.0f * (((b - r) / delta) + 2.0f);
        } else if(cMax == b) {
            h = 60.0f * (((r - g) / delta) + 4.0f);
        }

        if(cMax > 0.0f) {
            s = delta / cMax;
        } else {
            s = 0.0f;
        }

        v = cMax;
    } else {
        h = 0.0f;
        s = 0.0f;
        v = cMax;
    }

    if(h < 0.0f) {
        h = 360.0f + h;
    }
}

static void HSV2RGB(
    const float h,
    const float s,
    const float v,
    float& r,
    float& g,
    float& b)
{
    float c = v * s;
    float hPrime = static_cast<float>(std::fmod(h / 60.0f, 6));
    float x = c * (1 - std::fabs(std::fmod(hPrime, 2.0f) - 1.0f));
    float m = v - c;

    if(0.0f <= hPrime && hPrime < 1.0f) {
        r = c;
        g = x;
        b = 0.0f;
    } else if(1.0f <= hPrime && hPrime < 2.0f) {
        r = x;
        g = c;
        b = 0.0f;
    } else if(2.0f <= hPrime && hPrime < 3.0f) {
        r = 0.0f;
        g = c;
        b = x;
    } else if(3.0f <= hPrime && hPrime < 4.0f) {
        r = 0.0f;
        g = x;
        b = c;
    } else if(4.0f <= hPrime && hPrime < 5.0f) {
        r = x;
        g = 0.0f;
        b = c;
    } else if(5.0f <= hPrime && hPrime < 6.0f) {
        r = c;
        g = 0.0f;
        b = x;
    } else {
        r = 0.0f;
        g = 0.0f;
        b = 0.0f;
    }

    r += m;
    g += m;
    b += m;
}

inline float clip(
    const float n,
    const float lower,
    const float upper)
{
    return std::max(lower, std::min(n, upper));
}

std::unique_ptr<IConverter> CreateConverter()
{
    return std::make_unique<Converter>();
}

std::unique_ptr<YUVImage> Converter::Convert(
    const RGBImageView& image,
    const YUVType imageType) const
{
    auto result = std::make_unique<YUVImage>(
        image.GetWidth(), image.GetHeight());
    std::size_t size = result->GetWidth() * result->GetHeight() * 3;
    std::vector<std::size_t> shape = {
        result->GetWidth(), result->GetHeight(), 3 };
    auto xtInput = xt::cast<float>(
        xt::adapt(image.GetData(),
            size,
            xt::no_ownership(),
            shape));
    auto r = xt::view(xtInput, xt::all(), xt::all(), 0u);
    auto g = xt::view(xtInput, xt::all(), xt::all(), 1u);
    auto b = xt::view(xtInput, xt::all(), xt::all(), 2u);
    auto xtResult = xt::adapt(
        result->GetData(),
        size,
        xt::no_ownership(),
        shape);
    if (YUVType::YUV_BT601 == imageType) {
        auto y = r *  .257f + g *  .504f + b *  .098f +  16.0f;
        auto u = r * -.148f + g * -.291f + b *  .439f + 128.0f;
        auto v = r *  .439f + g * -.368f + b * -.071f + 128.0f;
        xt::view(xtResult, xt::all(), xt::all(), 0u) = xt::cast<uint8_t>(
            xt::clip(y, 0.0f, 255.0f));
        xt::view(xtResult, xt::all(), xt::all(), 1u) = xt::cast<uint8_t>(
            xt::clip(u, 0.0f, 255.0f));
        xt::view(xtResult, xt::all(), xt::all(), 2u) = xt::cast<uint8_t>(
            xt::clip(v, 0.0f, 255.0f));
    } else if (YUVType::YUV_BT709 == imageType) {
        auto y = r *  .183f + g *  .614f + b *  .062f +  16.0f;
        auto u = r * -.101f + g * -.338f + b *  .439f + 128.0f;
        auto v = r *  .439f + g * -.399f + b * -.040f + 128.0f;
        xt::view(xtResult, xt::all(), xt::all(), 0u) = xt::cast<uint8_t>(
            xt::clip(y, 0.0f, 255.0f));
        xt::view(xtResult, xt::all(), xt::all(), 1u) = xt::cast<uint8_t>(
            xt::clip(u, 0.0f, 255.0f));
        xt::view(xtResult, xt::all(), xt::all(), 2u) = xt::cast<uint8_t>(
            xt::clip(v, 0.0f, 255.0f));
    }
    return result;
}

std::unique_ptr<HSVImage> Converter::Convert(
    const RGBImageView& image) const
{
    auto result = std::make_unique<HSVImage>(
        image.GetWidth(), image.GetHeight());
    std::size_t size = image.GetWidth() * image.GetHeight() * 3;
    std::vector<std::size_t> shape = {
        image.GetWidth(), image.GetHeight(), 3 };
    xt::xarray<float> xtInput = xt::cast<float>(
        xt::adapt(
            image.GetData(),
            size,
            xt::no_ownership(),
            shape));

    xtInput /= 255.0f;

    auto xtResult = xt::adapt(
        result->GetData(),
        size,
        xt::no_ownership(),
        shape);

    for (std::size_t i = 0; i < xtInput.shape(0); i++) {
        for (std::size_t j = 0; j < xtInput.shape(1); j++) {
            float r = xtInput(i, j, 0);
            float g = xtInput(i, j, 1);
            float b = xtInput(i, j, 2);
            float h = 0.0f;
            float s = 0.0f;
            float v = 0.0f;
            RGB2HSV(r, g, b, h, s, v);
            xtResult(i, j, 0) = h;
            xtResult(i, j, 1) = s;
            xtResult(i, j, 2) = v;
        }
    }
    return result;
}

void Converter::Convert(
    RGBImageView outputImage,
    const std::unique_ptr<YUVImage>& inputImage,
    const YUVType imageType) const
{
    std::size_t size = outputImage.GetWidth() * outputImage.GetHeight() * 3;
    std::vector<std::size_t> shape = {
        outputImage.GetWidth(), outputImage.GetHeight(), 3 };
    auto xtInput = xt::cast<float>(
        xt::adapt(inputImage->GetData(),
            size,
            xt::no_ownership(),
            shape));
    auto y = xt::view(xtInput, xt::all(), xt::all(), 0u);
    auto u = xt::view(xtInput, xt::all(), xt::all(), 1u);
    auto v = xt::view(xtInput, xt::all(), xt::all(), 2u);
    auto xtResult = xt::adapt(
        outputImage.GetData(),
        size,
        xt::no_ownership(),
        shape);
    if (YUVType::YUV_BT601 == imageType) {
        auto r = 1.164f * (y - 16.0f) + 1.596f * (v - 128.0f);
        auto g = 1.164f * (y - 16.0f) - 0.813f * (v - 128.0f) - 0.391f * (u - 128.0f);
        auto b = 1.164f * (y - 16.0f) + 2.018f * (u - 128.0f);
        xt::view(xtResult, xt::all(), xt::all(), 0u) = xt::cast<uint8_t>(
            xt::clip(r, 0.0f, 255.0f));
        xt::view(xtResult, xt::all(), xt::all(), 1u) = xt::cast<uint8_t>(
            xt::clip(g, 0.0f, 255.0f));
        xt::view(xtResult, xt::all(), xt::all(), 2u) = xt::cast<uint8_t>(
            xt::clip(b, 0.0f, 255.0f));
    } else if (YUVType::YUV_BT709 == imageType) {
        auto r = 1.164f * (y - 16.0f) + 1.793f * (v - 128.0f);
        auto g = 1.164f * (y - 16.0f) - 0.534f * (v - 128.0f) - 0.213f * (u - 128.0f);
        auto b = 1.164f * (y - 16.0f) + 2.115f * (u - 128.0f);
        xt::view(xtResult, xt::all(), xt::all(), 0u) = xt::cast<uint8_t>(
            xt::clip(r, 0.0f, 255.0f));
        xt::view(xtResult, xt::all(), xt::all(), 1u) = xt::cast<uint8_t>(
            xt::clip(g, 0.0f, 255.0f));
        xt::view(xtResult, xt::all(), xt::all(), 2u) = xt::cast<uint8_t>(
            xt::clip(b, 0.0f, 255.0f));
    }
}

void Converter::Convert(
    RGBImageView outputImage,
    const std::unique_ptr<HSVImage>& inputImage) const
{
    std::size_t size = outputImage.GetWidth() * outputImage.GetHeight() * 3;
    std::vector<std::size_t> shape = {
        outputImage.GetWidth(), outputImage.GetHeight(), 3 };
    auto xtInput = xt::cast<float>(
        xt::adapt(inputImage->GetData(),
            size,
            xt::no_ownership(),
            shape));
    auto xtResult = xt::adapt(
        outputImage.GetData(),
        size,
        xt::no_ownership(),
        shape);
    for (std::size_t i = 0; i < xtInput.shape(0); i++) {
        for (std::size_t j = 0; j < xtInput.shape(1); j++) {
            float h = xtInput(i, j, 0);
            float s = xtInput(i, j, 1);
            float v = xtInput(i, j, 2);
            float r = 0.0f;
            float g = 0.0f;
            float b = 0.0f;
            HSV2RGB(h, s, v, r, g, b);
            xtResult(i, j, 0) = static_cast<uint8_t>(clip(r * 255.0f, 0.0f, 255.0f));
            xtResult(i, j, 1) = static_cast<uint8_t>(clip(g * 255.0f, 0.0f, 255.0f));
            xtResult(i, j, 2) = static_cast<uint8_t>(clip(b * 255.0f, 0.0f, 255.0f));
        }
    }
}

}

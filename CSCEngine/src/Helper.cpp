#include "Helper.hpp"

#include <xtensor/xarray.hpp>
#include <xtensor/xadapt.hpp>
#include <xtensor/xview.hpp>

namespace CSCEngine
{

using namespace xt::placeholders;

static constexpr float H_SCALE = 0.1f;
static constexpr float S_SCALE = 0.001f;
static constexpr float V_SCALE = 0.001f;

void Helper::H2RGB(
    const std::unique_ptr<HSVImage>& inputImage,
    RGBImageView outputImage)
{
    std::size_t size = inputImage->GetWidth() * inputImage->GetHeight() * 3;
    std::vector<std::size_t> shape = {
        inputImage->GetWidth(), inputImage->GetHeight(), 3 };
    auto xtInput = xt::adapt(
        inputImage->GetData(),
        size,
        xt::no_ownership(),
        shape);
    xt::xarray<float> h = xt::view(xtInput, xt::all(), xt::all(), 0u);
    h *= 255.0f / 360.0f;
    auto xtResult = xt::adapt(
        outputImage.GetData(),
        size,
        xt::no_ownership(),
        shape);
    xt::view(xtResult, xt::all(), xt::all(), 0u) =
        xt::cast<uint8_t>(xt::clip(h, 0.0f, 255.0f));
    xt::view(xtResult, xt::all(), xt::all(), 1u) =
        xt::cast<uint8_t>(xt::clip(h, 0.0f, 255.0f));
    xt::view(xtResult, xt::all(), xt::all(), 2u) =
        xt::cast<uint8_t>(xt::clip(h, 0.0f, 255.0f));
}

void Helper::S2RGB(
    const std::unique_ptr<HSVImage>& inputImage,
    RGBImageView outputImage)
{
    std::size_t size = inputImage->GetWidth() * inputImage->GetHeight() * 3;
    std::vector<std::size_t> shape = {
        inputImage->GetWidth(), inputImage->GetHeight(), 3 };
    auto xtInput = xt::adapt(
        inputImage->GetData(),
        size,
        xt::no_ownership(),
        shape);
    xt::xarray<float> s = xt::view(xtInput, xt::all(), xt::all(), 1u);
    s *= 255.0f;
    auto xtResult = xt::adapt(
        outputImage.GetData(),
        size,
        xt::no_ownership(),
        shape);
    xt::view(xtResult, xt::all(), xt::all(), 0u) =
        xt::cast<uint8_t>(xt::clip(s, 0.0f, 255.0f));
    xt::view(xtResult, xt::all(), xt::all(), 1u) =
        xt::cast<uint8_t>(xt::clip(s, 0.0f, 255.0f));
    xt::view(xtResult, xt::all(), xt::all(), 2u) =
        xt::cast<uint8_t>(xt::clip(s, 0.0f, 255.0f));
}

void Helper::V2RGB(
    const std::unique_ptr<HSVImage>& inputImage,
    RGBImageView outputImage)
{
    std::size_t size = inputImage->GetWidth() * inputImage->GetHeight() * 3;
    std::vector<std::size_t> shape = {
        inputImage->GetWidth(), inputImage->GetHeight(), 3 };
    auto xtInput = xt::adapt(
        inputImage->GetData(),
        size,
        xt::no_ownership(),
        shape);
    xt::xarray<float> v = xt::view(xtInput, xt::all(), xt::all(), 2u);
    v *= 255.0f;
    auto xtResult = xt::adapt(
        outputImage.GetData(),
        size,
        xt::no_ownership(),
        shape);
    xt::view(xtResult, xt::all(), xt::all(), 0u) =
        xt::cast<uint8_t>(xt::clip(v, 0.0f, 255.0f));
    xt::view(xtResult, xt::all(), xt::all(), 1u) =
        xt::cast<uint8_t>(xt::clip(v, 0.0f, 255.0f));
    xt::view(xtResult, xt::all(), xt::all(), 2u) =
        xt::cast<uint8_t>(xt::clip(v, 0.0f, 255.0f));
}

void Helper::Y2RGB(
    const std::unique_ptr<YUVImage>& inputImage,
    RGBImageView outputImage)
{
    std::size_t size = inputImage->GetWidth() * inputImage->GetHeight() * 3;
    std::vector<std::size_t> shape = {
        inputImage->GetWidth(), inputImage->GetHeight(), 3 };
    auto xtInput = xt::adapt(
        inputImage->GetData(),
        size,
        xt::no_ownership(),
        shape);
    auto y = xt::view(xtInput, xt::all(), xt::all(), 0u);
    auto xtResult = xt::adapt(
        outputImage.GetData(),
        size,
        xt::no_ownership(),
        shape);
    xt::view(xtResult, xt::all(), xt::all(), 0u) = y;
    xt::view(xtResult, xt::all(), xt::all(), 1u) = y;
    xt::view(xtResult, xt::all(), xt::all(), 2u) = y;
}

void Helper::U2RGB(
    const std::unique_ptr<YUVImage>& inputImage,
    RGBImageView outputImage)
{
    std::size_t size = inputImage->GetWidth() * inputImage->GetHeight() * 3;
    std::vector<std::size_t> shape = {
        inputImage->GetWidth(), inputImage->GetHeight(), 3 };
    auto xtInput = xt::adapt(
        inputImage->GetData(),
        size,
        xt::no_ownership(),
        shape);
    auto u = xt::view(xtInput, xt::all(), xt::all(), 1u);
    auto xtResult = xt::adapt(
        outputImage.GetData(),
        size,
        xt::no_ownership(),
        shape);
    xt::view(xtResult, xt::all(), xt::all(), 0u) = u;
    xt::view(xtResult, xt::all(), xt::all(), 1u) = u;
    xt::view(xtResult, xt::all(), xt::all(), 2u) = u;
}

void Helper::V2RGB(
    const std::unique_ptr<YUVImage>& inputImage,
    RGBImageView outputImage)
{
    std::size_t size = inputImage->GetWidth() * inputImage->GetHeight() * 3;
    std::vector<std::size_t> shape = {
        inputImage->GetWidth(), inputImage->GetHeight(), 3 };
    auto xtInput = xt::adapt(
        inputImage->GetData(),
        size,
        xt::no_ownership(),
        shape);
    auto v = xt::view(xtInput, xt::all(), xt::all(), 2u);
    auto xtResult = xt::adapt(
        outputImage.GetData(),
        size,
        xt::no_ownership(),
        shape);
    xt::view(xtResult, xt::all(), xt::all(), 0u) = v;
    xt::view(xtResult, xt::all(), xt::all(), 1u) = v;
    xt::view(xtResult, xt::all(), xt::all(), 2u) = v;
}

void Helper::ChangeH(
    std::unique_ptr<HSVImage>& image,
    int value)
{
    std::size_t size = image->GetWidth() * image->GetHeight() * 3;
    std::vector<std::size_t> shape = {
        image->GetWidth(), image->GetHeight(), 3 };
    xt::xarray<float> xtInput = xt::adapt(
        image->GetData(),
        size,
        xt::no_ownership(),
        shape);
    xt::view(xtInput, xt::all(), xt::all(), 0u) += float(value) * H_SCALE;
    auto xtResult = xt::adapt(
        image->GetData(),
        size,
        xt::no_ownership(),
        shape);
    xtResult = xt::clip(xtInput, 0.0f, 360.0f);
}

void Helper::ChangeS(
    std::unique_ptr<HSVImage>& image,
    int value)
{
    std::size_t size = image->GetWidth() * image->GetHeight() * 3;
    std::vector<std::size_t> shape = {
        image->GetWidth(), image->GetHeight(), 3 };
    xt::xarray<float> xtInput = xt::adapt(
        image->GetData(),
        size,
        xt::no_ownership(),
        shape);
    xt::view(xtInput, xt::all(), xt::all(), 1u) += float(value) * S_SCALE;
    auto xtResult = xt::adapt(
        image->GetData(),
        size,
        xt::no_ownership(),
        shape);
    xtResult = xt::clip(xtInput, 0.0f, 1.0f);
}

void Helper::ChangeV(
    std::unique_ptr<HSVImage>& image,
    int value)
{
    std::size_t size = image->GetWidth() * image->GetHeight() * 3;
    std::vector<std::size_t> shape = {
        image->GetWidth(), image->GetHeight(), 3 };
    xt::xarray<float> xtInput = xt::adapt(
        image->GetData(),
        size,
        xt::no_ownership(),
        shape);
    xt::view(xtInput, xt::all(), xt::all(), 2u) += float(value) * V_SCALE;
    auto xtResult = xt::adapt(
        image->GetData(),
        size,
        xt::no_ownership(),
        shape);
    xtResult = xt::clip(xtInput, 0.0f, 1.0f);
}

void Helper::ChangeY(
    std::unique_ptr<YUVImage>& image,
    int value)
{
    std::size_t size = image->GetWidth() * image->GetHeight() * 3;
    std::vector<std::size_t> shape = {
        image->GetWidth(), image->GetHeight(), 3 };
    xt::xarray<float> xtInput = xt::cast<float>(
        xt::adapt(
            image->GetData(),
            size,
            xt::no_ownership(),
            shape));
    xt::view(xtInput, xt::all(), xt::all(), 0u) += float(value);
    auto xtResult = xt::adapt(
        image->GetData(),
        size,
        xt::no_ownership(),
        shape);
    xtResult = xt::cast<uint8_t>(xt::clip(xtInput, 0.0f, 255.0f));
}

void Helper::ChangeU(
    std::unique_ptr<YUVImage>& image,
    int value)
{
    std::size_t size = image->GetWidth() * image->GetHeight() * 3;
    std::vector<std::size_t> shape = {
        image->GetWidth(), image->GetHeight(), 3 };
    xt::xarray<float> xtInput = xt::cast<float>(
        xt::adapt(
            image->GetData(),
            size,
            xt::no_ownership(),
            shape));
    xt::view(xtInput, xt::all(), xt::all(), 1u) += float(value);
    auto xtResult = xt::adapt(
        image->GetData(),
        size,
        xt::no_ownership(),
        shape);
    xtResult = xt::cast<uint8_t>(xt::clip(xtInput, 0.0f, 255.0f));
}

void Helper::ChangeV(
    std::unique_ptr<YUVImage>& image,
    int value)
{
    std::size_t size = image->GetWidth() * image->GetHeight() * 3;
    std::vector<std::size_t> shape = {
        image->GetWidth(), image->GetHeight(), 3 };
    xt::xarray<float> xtInput = xt::cast<float>(
        xt::adapt(
            image->GetData(),
            size,
            xt::no_ownership(),
            shape));
    xt::view(xtInput, xt::all(), xt::all(), 2u) += float(value);
    auto xtResult = xt::adapt(
        image->GetData(),
        size,
        xt::no_ownership(),
        shape);
    xtResult = xt::cast<uint8_t>(xt::clip(xtInput, 0.0f, 255.0f));
}

}

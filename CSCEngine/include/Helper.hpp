#pragma once

#include "Image.hpp"
#include "Types.hpp"

namespace CSCEngine
{

class Helper
{
public:
    static void H2RGB(
        const std::unique_ptr<HSVImage>& inputImage,
        RGBImageView outputImage);
    static void S2RGB(
        const std::unique_ptr<HSVImage>& inputImage,
        RGBImageView outputImage);
    static void V2RGB(
        const std::unique_ptr<HSVImage>& inputImage,
        RGBImageView outputImage);
    static void Y2RGB(
        const std::unique_ptr<YUVImage>& inputImage,
        RGBImageView outputImage);
    static void U2RGB(
        const std::unique_ptr<YUVImage>& inputImage,
        RGBImageView outputImage);
    static void V2RGB(
        const std::unique_ptr<YUVImage>& inputImage,
        RGBImageView outputImage);
    static void ChangeH(
        std::unique_ptr<HSVImage>& image,
        const int value);
    static void ChangeS(
        std::unique_ptr<HSVImage>& image,
        const int value);
    static void ChangeV(
        std::unique_ptr<HSVImage>& image,
        const int value);
    static void ChangeY(
        std::unique_ptr<YUVImage>& image,
        const int value);
    static void ChangeU(
        std::unique_ptr<YUVImage>& image,
        const int value);
    static void ChangeV(
        std::unique_ptr<YUVImage>& image,
        const int value);
};

}

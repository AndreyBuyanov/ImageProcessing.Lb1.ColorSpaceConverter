#pragma once

#include <cstdint>
#include <memory>
#include <vector>

namespace CSCEngine
{

template <typename T>
class Abstract3ChannelImage
{
public:
    using data_t = typename std::vector<T>::pointer;
    using const_data_t = typename std::vector<T>::const_pointer;
public:
    Abstract3ChannelImage(
        const std::size_t width,
        const std::size_t height)
        : m_width(width)
        , m_height(height)
        , m_data(width * height * 3) {}
    [[nodiscard]] const_data_t GetData() const
    {
        return m_data.data();
    }
    [[nodiscard]] data_t GetData()
    {
        return m_data.data();
    }
    [[nodiscard]] std::size_t GetWidth() const
    {
        return m_width;
    }
    [[nodiscard]] std::size_t GetHeight() const
    {
        return m_height;
    }
private:
    std::vector<T> m_data;
    std::size_t m_width = 0;
    std::size_t m_height = 0;
};


using YUVImage = Abstract3ChannelImage<std::uint8_t>;

using HSVImage = Abstract3ChannelImage<float>;

class RGBImageView
{
public:
    using data_t = std::uint8_t*;
    using const_data_t = const std::uint8_t*;
public:
    RGBImageView() = default;
    RGBImageView(
        std::uint8_t* data,
        const std::size_t width,
        const std::size_t height)
        : m_data(data)
        , m_width(width)
        , m_height(height) {}
    [[nodiscard]] const_data_t GetData() const
    {
        return m_data;
    }
    [[nodiscard]] data_t GetData()
    {
        return m_data;
    }
    [[nodiscard]] std::size_t GetWidth() const
    {
        return m_width;
    }
    [[nodiscard]] std::size_t GetHeight() const
    {
        return m_height;
    }
private:
    std::uint8_t* m_data = nullptr;
    std::size_t m_width = 0;
    std::size_t m_height = 0;
};

}

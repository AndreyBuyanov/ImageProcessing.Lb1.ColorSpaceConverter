#pragma once

#include <cstdint>
#include <memory>
#include <vector>

namespace CSCEngine
{

template <typename T>
struct pointer_wrapper
{
    using data_t = T*;
    using const_data_t = const T*;
};

template <typename T>
class Abstract3ChannelImage
{
public:
    using data_t = typename std::vector<T>::pointer;
    using const_data_t = typename std::vector<T>::const_pointer;
    using value_t = typename std::vector<T>::value_type;
public:
    Abstract3ChannelImage(
        const std::size_t width,
        const std::size_t height)
        : m_width(width)
        , m_height(height)
        , m_data(width * height * 3) {}
    const_data_t GetData() const
    {
        return m_data.data();
    }
    data_t GetData()
    {
        return m_data.data();
    }
    std::size_t GetWidth() const
    {
        return m_width;
    }
    std::size_t GetHeight() const
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
    using data_t = typename pointer_wrapper<std::uint8_t>::data_t;
    using const_data_t = typename pointer_wrapper<std::uint8_t>::const_data_t;
public:
    RGBImageView() = default;
    RGBImageView(
        std::uint8_t* data,
        const std::size_t width,
        const std::size_t height)
        : m_data(data)
        , m_width(width)
        , m_height(height) {}
    const_data_t GetData() const
    {
        return m_data;
    }
    data_t GetData()
    {
        return m_data;
    }
    std::size_t GetWidth() const
    {
        return m_width;
    }
    std::size_t GetHeight() const
    {
        return m_height;
    }
private:
    std::uint8_t* m_data = nullptr;
    std::size_t m_width = 0;
    std::size_t m_height = 0;
};

}

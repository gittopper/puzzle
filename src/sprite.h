#pragma once

#include <vector>

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a = 255;
};

class Sprite {
  public:
    enum Type { RGBA, RGB };
    Sprite(std::size_t width,
           std::size_t height,
           std::size_t gl_width,
           std::size_t gl_height,
           Type type,
           std::vector<unsigned char>&& data) :
        width_(width),
        height_(height),
        gl_width_(gl_width),
        gl_height_(gl_height),
        type_(type),
        data_(std::move(data)) {}
    std::size_t width() const {
        return width_;
    }
    std::size_t height() const {
        return height_;
    }
    std::size_t glWidth() const {
        return gl_width_;
    }
    std::size_t glHeight() const {
        return gl_height_;
    }
    const unsigned char* data() const {
        return data_.data();
    }
    void setPixel(std::size_t x, std::size_t y, const Color& color) {
        auto shift = (y * glWidth() + x) * (type_ == RGBA ? 4 : 3);
        data_[shift] = color.r;
        data_[shift + 1] = color.g;
        data_[shift + 2] = color.b;
        if (type_ == RGBA) {
            data_[shift + 3] = color.a;
        }
    }
    Type type() const {
        return type_;
    }

  private:
    std::size_t width_;
    std::size_t height_;
    std::size_t gl_width_;
    std::size_t gl_height_;
    Type type_;
    std::vector<unsigned char> data_;
};

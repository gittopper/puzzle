#pragma once

#include <freetype/freetype.h>

#include <sprite.h>
#include <stdio.h>
#include <string>
#include <uchar.h>
#include <vector>

using UString = std::basic_string<char32_t>;

class Font {
  public:
    Font(std::vector<char> font_ttf_data, int font_size = 12);
    void setFontSize(int size);
    void setColor(const Color& color) {
        color_ = color;
    }
    void renderText(Sprite& sprite,
                    std::size_t x,
                    std::size_t y,
                    const UString& text);

  private:
    std::vector<char> font_ttf_data_;
    FT_Library library_;
    FT_Face face_;
    Color color_ = {0, 0, 0, 255};
};

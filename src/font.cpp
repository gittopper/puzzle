#include <font.h>
#include <stdexcept>

Font::Font(std::vector<char> font_ttf_data, int font_size) :
    font_ttf_data_(std::move(font_ttf_data)) {
    if (FT_Init_FreeType(&library_)) {
        throw std::runtime_error("FT_Init_FreeType failed");
    }
    if (FT_New_Memory_Face(library_,
                           reinterpret_cast<FT_Byte*>(font_ttf_data_.data()),
                           font_ttf_data_.size(), 0, &face_)) {
        throw std::runtime_error("FT_Init_FreeType failed");
    }
    setFontSize(font_size);
}

void Font::setFontSize(int font_size) {
    FT_Set_Char_Size(face_, font_size << 6, font_size << 6, 64, 64);
}

void Font::renderText(Sprite& sprite,
                      std::size_t x,
                      std::size_t y,
                      const UString& text) {
    auto cur_x = x;
    auto ascender = face_->ascender >> 6;
    for (auto& symbol : text) {
        FT_UInt glyph_index = FT_Get_Char_Index(face_, symbol);
        if (FT_Load_Glyph(face_, glyph_index, FT_LOAD_RENDER)) {
            throw std::runtime_error("FT_Load_Glyph failed");
        }
        FT_Bitmap* bitmap = &(face_->glyph->bitmap);
        auto glyph_x = cur_x + face_->glyph->bitmap_left;
        auto glyph_y = y + ascender - face_->glyph->bitmap_top;
        auto color = color_;
        for (auto c = 0; c < bitmap->width; ++c) {
            for (auto r = 0; r < bitmap->rows; ++r) {
                auto gray = bitmap->buffer[r * bitmap->pitch + c];
                color.a = gray;
                if (gray > 0) {
                    sprite.setPixel(glyph_x + c, glyph_y + r, color);
                }
            }
        }
        cur_x += (face_->glyph->advance.x >> 6);
    }
}

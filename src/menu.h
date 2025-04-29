#pragma once

#include <font.h>

struct MenuConfig {
    int item_padding = 10;
    int menu_x_shift = 10;
    int menu_y_shift = 10;
    int font_size = 50;
    Color font_color = {255, 0, 255, 100};
    Color button_color = {155, 155, 155, 155};
};

class Menu {
  public:
    Menu(FontPtr font, MenuConfig config = MenuConfig()) :
        font_(std::move(font)), config_(std::move(config)) {}
    void setItems(std::vector<UString> menu_items) {
        menu_items_ = std::move(menu_items);
    }
    void render(Sprite& sprite);
    int selectItem(int x, int y) const;
    const std::vector<UString>& items() const {
        return menu_items_;
    }

  private:
    std::vector<UString> menu_items_;
    std::vector<Rect2D> item_rects_;
    FontPtr font_;
    MenuConfig config_;
};

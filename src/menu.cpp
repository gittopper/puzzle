#include <menu.h>

void Menu::render(Sprite& sprite) {
    font_->setColor(config_.font_color);
    font_->setFontSize(config_.font_size);
    item_rects_.clear();
    int menu_x_shift = config_.menu_x_shift;
    int menu_y_shift = config_.menu_y_shift;
    int max_width = 0;
    for (auto& item : menu_items_) {
        auto item_rect = font_->getTextRect(item);
        item_rect.x = menu_x_shift;
        item_rect.y = menu_y_shift;
        menu_y_shift += config_.item_padding + item_rect.height;
        max_width = std::max(max_width, item_rect.width);
        item_rects_.push_back(item_rect);
        font_->renderText(sprite, item_rect.x, item_rect.y, item);
    }
    for (auto& item : item_rects_) {
        item.width = max_width;
        sprite.drawRect(item.x, item.y, item.width, item.height,
                        config_.button_color);
    }
    for (auto i = 0UL; i < menu_items_.size(); ++i) {
        auto& item_text = menu_items_[i];
        auto& item_rect = item_rects_[i];
        font_->renderText(sprite, item_rect.x, item_rect.y, item_text);
    }
}

int Menu::selectItem(int x, int y) const {
    int selected_item = -1;
    for (auto i = 0UL; i < item_rects_.size(); ++i) {
        if (item_rects_[i].isInside(x, y)) {
            selected_item = i;
        }
    }
    return selected_item;
}

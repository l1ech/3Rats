#pragma once

#include "Item.h"
#include <vector>

class ItemManager {
public:
    ItemManager();
    ~ItemManager();

    void addItem(Item* item);
    void removeItem(size_t index);
    Item* getItem(size_t index) const;

    void draw_all(SDL_Renderer* renderTarget) const;

private:
    static const size_t MAX_ITEMS = 100;
    std::vector<Item*> items;
};
#include "ItemManager.h"
#include <algorithm> // for std::remove

const size_t MAX_ITEMS = 100; // Define a maximum size for the array

ItemManager::ItemManager() {
    items.reserve(MAX_ITEMS);
}

ItemManager::~ItemManager() {
    for (Item* item : items) {
        delete item;
    }
}

void ItemManager::removeItem(size_t index) {
    if (index < items.size()) {
        delete items[index];
        items[index] = items.back();
        items.pop_back();
    }
}

void ItemManager::addItem(Item* item) {
    if (items.size() < MAX_ITEMS) {
        items.push_back(item);
    }
}

Item* ItemManager::getItem(size_t index) const {
    if (index < items.size()) {
        return items[index];
    }
    return nullptr;
}

void ItemManager::draw(SDL_Renderer* renderTarget) const {
    for (Item* item : items) {
        item->Draw(renderTarget);
    }
}
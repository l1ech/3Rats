#include "Inventory.h"

Inventory::Inventory()
{
}

void Inventory::push_item(Item* item)
{
    if (inventory.size() <= max_size)
    {
        inventory.push_back(item);
    }
    else
    {
        std::cout << "ERROR: Inventory is full!" << std::endl;
    }
    
}

Item* Inventory::pop_item()
{
    Item* item = inventory.back();
    inventory.pop_back();
    return item;
}

void Inventory::re_size(int newSize)
{
    max_size = newSize;
}
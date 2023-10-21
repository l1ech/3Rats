#include "Inventory.h"

Inventory::Inventory()
{
    size = 1;

}

void Inventory::init()
{
}

void Inventory::push_item(Item* item)
{
    if (inventory.size() <= size)
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
    size = newSize;
}
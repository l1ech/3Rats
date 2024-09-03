#include "Inventory.h"

Inventory::Inventory()
{
}

void Inventory::push_prop(Prop* prop)
{
    if (inventory.size() <= max_size)
    {
        inventory.push_back(prop);
    }
    else
    {
        std::cout << "ERROR: Inventory is full!" << std::endl;
    }
    
}

Prop* Inventory::pop_prop()
{
    Prop* prop = inventory.back();
    inventory.pop_back();
    return prop;
}

void Inventory::re_size(int newSize)
{
    max_size = newSize;
}
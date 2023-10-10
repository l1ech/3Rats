#include "Inventory.h"

Inventory::Inventory()
{
	inventory_slots[3];
}

Inventory::Inventory(int player_amount)
{

	inventory_slots[player_amount];

}

void Inventory::init_inventory(int player_amount)
{
	for (int i = 0; i < player_amount; i++)
	{
		inventory_slots[i] = 0;
	}
}

void Inventory::set_item_at(int index, int item)
{
	inventory_slots[index] = item;
}

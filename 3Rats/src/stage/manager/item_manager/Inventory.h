#pragma once

#include "../../Item.h"

// normaly i should use some kind of array of items 
// but for testing lets do it with int

class Inventory
{
private:
	//Item inventory_slots[];
	int inventory_slots[];
public:
	Inventory();
	Inventory(int player_amount);

	void init_inventory(int player_amount);

	void set_item_at(int index, int item);
};
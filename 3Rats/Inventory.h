#pragma once

#include "Item.h"

#include <vector>

// normaly i should use some kind of array of items 
// but for testing lets do it with int

class Inventory
{
protected:
	Item empty_item;
	std::vector<Item*> inventory;
	int max_size;
public:
	Inventory();

	void push_item(Item* item);
	Item* pop_item();
	void re_size(int newSize);
};
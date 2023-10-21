#pragma once

#include "Item.h"

#include <vector>

// normaly i should use some kind of array of items 
// but for testing lets do it with int

class Inventory
{
protected:
	std::vector<Item*> inventory;
	int size;
public:
	Inventory();
	void init();

	void push_item(Item* item);
	Item* pop_item();
	void re_size(int newSize);
};
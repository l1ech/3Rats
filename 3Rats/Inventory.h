#pragma once

#include "Prop.h"

#include <vector>

// normaly i should use some kind of array of props 
// but for testing lets do it with int

class Inventory
{
protected:
	Prop empty_prop;
	std::vector<Prop*> inventory;
	int max_size;
public:
	Inventory();

	void push_prop(Prop* prop);
	Prop* pop_prop();
	void re_size(int newSize);
};
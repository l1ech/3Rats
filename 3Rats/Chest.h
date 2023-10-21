#pragma once

#include "Inventory.h"

class Chest : public Inventory, public Body
{
public:
	Chest();
	~Chest();
};
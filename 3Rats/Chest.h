#pragma once

#include "Inventory.h"
#include "Body.h"

class Chest : public Body, public Inventory
{
public:
	Chest();
	~Chest();
};
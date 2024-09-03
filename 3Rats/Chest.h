#pragma once

#include "Inventory.h"
#include "Body.h"

class Chest : public Body, public Inventory
{
private:
	int chest_level;
public:
	Chest();
	~Chest();

	void update(double delta);

	Prop* get_prop();
};
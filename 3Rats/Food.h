#pragma once

#include "Item.h"
#include "Random.h"

class Food : public Item
{
private:
	int taste;
	int colour;
	int texture;
	int appearence;
	int freshness;
	int duration;
	int nutritions;
	int temperature;

public:
	Food();

};
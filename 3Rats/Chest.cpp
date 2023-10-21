#include "Chest.h"

Chest::Chest()
{
}

Chest::~Chest()
{
}

void Chest::update(double delta)
{
	chest_level = inventory.size();
}

Item* Chest::get_item()
{
	if (chest_level != 0)
	{
		crop_rect.y += frame_height;
		return pop_item();
	}
	else
	{
		std::cout << "chest empty!" << std::endl;
	}
}

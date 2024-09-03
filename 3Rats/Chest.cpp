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

Prop* Chest::get_prop()
{
	if (chest_level != 0)
	{
		crop_rect.y += frame_height;
		return pop_prop();
	}
	else
	{
		std::cout << "chest empty!" << std::endl;
	}
}

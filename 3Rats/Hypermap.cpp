#include "Hypermap.h"

Hypermap::Hypermap()
{
	number_items_on_map = 0;
}

void Hypermap::set_map_array(Map* arg, int size)
{
	map_array = arg;
	map_array_size = size;
}

void Hypermap::set_up()
{
	ptr = &number_items_on_map;

	for (int i = 0; i < map_array_size; i++)
	{
		map_array[i].set_ptr(ptr);
	}
}

void Hypermap::update(float delta)
{
	for (int i = 0; i < map_array_size; i++)
	{
		map_array[i].Update(delta);
	}
}

void Hypermap::draw(SDL_Renderer* renderTarget)
{
	for (int i = 0; i < map_array_size; i++)
	{
		map_array[i].Draw(renderTarget);
	}
}

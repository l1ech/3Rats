#include "Hypermap.h"

Hypermap::Hypermap()
{
	number_items_on_map = 0;
}

void Hypermap::set_map_array(Map* map, int map_size)
{
	map_array = map;
	map_array_size = map_size;
}

Map* Hypermap::get_map_array()
{
	return map_array;
}

void Hypermap::set_tile_array(Tile* tile, int tile_size)
{

	tile_array = tile;
	tile_array_size = tile_size;
}

Tile* Hypermap::get_tile_array()
{
	return tile_array;
}

int Hypermap::get_tile_size()
{
	return tile_array_size;
}

void Hypermap::set_item_array(Item* item, int item_size)
{
	item_array = item;
	item_array_size = item_size;
}

Item* Hypermap::get_item_array()
{
	return item_array;
}

int Hypermap::get_item_size()
{
	return item_array_size;
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
	//time += delta;

	for (int i = 0; i < map_array_size; i++)
	{
		//map_array[i].Update(delta);
	}
}

void Hypermap::draw(SDL_Renderer* renderTarget)
{
	for (int i = 0; i < map_array_size; i++)
	{
		//map_array[i].Draw(renderTarget);
	}
	for (int i = 0; i < tile_array_size; i++)
	{
		tile_array[i].Draw(renderTarget);
	}

	for (int i = 0; i < item_array_size; i++)
	{
		item_array[i].Draw(renderTarget);
	}
}

void Hypermap::set_renderer(SDL_Renderer* renderTarget)
{
	this->renderTarget = renderTarget;
}

Map* Hypermap::get_map()
{
	return map_array;
}

int Hypermap::get_map_size()
{
	return map_array_size;
}

#include "Level_Structure.h"

void Level_Structure::set_tile_array(Tile* tile, int tile_size)
{
	tile_array = tile;
	tile_array_size = tile_size;
}

Tile* Level_Structure::get_tile_array() { return tile_array; }

int Level_Structure::get_tile_size() { return tile_array_size; }

void Level_Structure::set_item_array(Item* item, int item_size)
{
	item_array = item;
	item_array_size = item_size;
}

Item* Level_Structure::get_item_array() { return item_array; }

int Level_Structure::get_item_size() { return item_array_size; }

void Level_Structure::set_random_pointer(Random& random) { random_ptr = &random; }


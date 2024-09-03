#include "Level_Structure.h"

void Level_Structure::set_tile_array(Tile* tile, int tile_size)
{
	tile_array = tile;
	tile_array_size = tile_size;
}

Tile* Level_Structure::get_tile_array() { return tile_array; }

int Level_Structure::get_tile_size() { return tile_array_size; }

void Level_Structure::set_prop_array(Prop* prop, int prop_size)
{
	prop_array = prop;
	prop_array_size = prop_size;
}

Prop* Level_Structure::get_prop_array() { return prop_array; }

int Level_Structure::get_prop_size() { return prop_array_size; }

void Level_Structure::set_random_pointer(Random& random) { random_ptr = &random; }


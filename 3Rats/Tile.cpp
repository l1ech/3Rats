#include "Body.h"
#include <memory>
#include "Tile.h"

Tile::Tile()
{
	is_entrance = false;
	is_exit = false;
	is_hole = false;

	file_path = "meta_textures/place_holder.png";
}

Tile::~Tile()
{
	//std::cout << "destructor" << std::endl;
}
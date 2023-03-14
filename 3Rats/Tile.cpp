#include "Body.h"
#include <memory>
#include "Tile.h"

Tile::Tile()
{
	is_entrance = false;
	is_exit = false;
	is_hole = false;

	filePath = "meta_textures/place_holder.png";
}

Tile::Tile(bool exit, bool entrance, bool hole, std::string path, int height)
{
	is_exit = exit;
	is_entrance = entrance;
	is_hole = hole;

	filePath = path;

	this->hight = height;
}
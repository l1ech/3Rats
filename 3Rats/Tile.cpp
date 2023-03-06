#include "Body.h"
#include <memory>
#include "Tile.h"

Tile::Tile()
{
	is_entrance = false;
	is_exit = false;

	filePath = "meta_textures/place_holder.png";
}

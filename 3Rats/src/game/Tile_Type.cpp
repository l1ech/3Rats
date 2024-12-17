#include "Tile_Type.h"

// Constructor definition without default arguments
TileType::TileType(std::string texture, bool exit, bool hole, bool entrance, int h) 
    : texture_path(texture), is_exit(exit), is_hole(hole), is_entrance(entrance), height(h) {}

void TileType::applyToTile(Tile& tile) const {
    tile.set_texture(texture_path);
    tile.is_exit = is_exit;
    tile.is_hole = is_hole;
    tile.is_entrance = is_entrance;
    tile.set_hight(height);
}

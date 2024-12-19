#include "Tile_Type.h"
#include <iostream> // Include for debugging messages

// Constructor definition without default arguments
TileType::TileType(std::string texture, bool exit, bool hole, bool entrance, int h) 
    : texture_path(texture), is_exit(exit), is_hole(hole), is_entrance(entrance), height(h) {
    // Log the creation of a TileType object
    std::cout << std::endl;
    std::cout << "[Tile_type]: TileType constructor: Created TileType with texture: " << texture_path 
              << ", Exit: " << is_exit << ", Hole: " << is_hole 
              << ", Entrance: " << is_entrance << ", Height: " << height << std::endl;
}

void TileType::applyToTile(Tile& tile) const {
    // Log the application of a TileType to a Tile object
    std::cout << std::endl;
    std::cout << "[Tile_type]: Applying TileType to Tile: "
              << "Texture: " << texture_path 
              << ", Exit: " << is_exit 
              << ", Hole: " << is_hole 
              << ", Entrance: " << is_entrance 
              << ", Height: " << height << std::endl;
    
    // Apply the properties of TileType to Tile
    tile.set_texture(texture_path);
    tile.is_exit = is_exit;
    tile.is_hole = is_hole;
    tile.is_entrance = is_entrance;
    tile.set_hight(height);
    tile.set_cords(0,0); //a TESET -----------

    // Log after applying to confirm the Tile has been updated
    std::cout << "[Tile_type]: Tile updated with Texture: " << texture_path
              << ", Exit: " << tile.is_exit
              << ", Hole: " << tile.is_hole
              << ", Entrance: " << tile.is_entrance
              << ", Height: " << tile.get_hight() << std::endl;
}

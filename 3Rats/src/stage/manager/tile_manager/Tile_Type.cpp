#include "Tile_Type.h"
#include <SDL2/SDL.h> // Include for SDL_Log

// Constructor definition without default arguments
TileType::TileType(std::string texture, bool exit, bool hole, bool entrance, int h) 
    : texture_path(texture), is_exit(exit), is_hole(hole), is_entrance(entrance), height(h) {
    // Log the creation of a TileType object using SDL_Log
    SDL_Log("TileType constructor: Created TileType with texture: %s, Exit: %d, Hole: %d, Entrance: %d, Height: %d", 
            texture_path.c_str(), is_exit, is_hole, is_entrance, height);
}

void TileType::applyToTile(Tile& tile, SDL_Renderer* render_target) const {
    // Log the application of a TileType to a Tile object
    SDL_Log("Applying TileType to Tile: Texture: %s, Exit: %d, Hole: %d, Entrance: %d, Height: %d", 
            texture_path.c_str(), is_exit, is_hole, is_entrance, height);
    
    // Apply the properties of TileType to Tile
    //tile.set_surface(render_target);
    tile.set_texture_path(texture_path);
    tile.is_exit = is_exit;
    tile.is_hole = is_hole;
    tile.is_entrance = is_entrance;
    tile.set_hight(height);
    tile.set_cords(0, 0); //a TEST -----------

    // Log after applying to confirm the Tile has been updated
    SDL_Log("Tile updated with Texture: %s, Exit: %d, Hole: %d, Entrance: %d, Height: %d", 
            texture_path.c_str(), tile.is_exit, tile.is_hole, tile.is_entrance, tile.get_hight());
}


#include "Tile_Manager.h"

TileManager::TileManager() {
    // Initialize the tile types with their respective properties and textures
    tile_types.push_back(TileType(collage.get_path(10), true, false, false, 0));  // end_door (maze_door.png)
    tile_types.push_back(TileType(collage.get_path(12), false, false, false, 0));  // horizontal (walk_way_shadow_horizontal.png)
    tile_types.push_back(TileType(collage.get_path(11), false, false, false, 1));  // wall (maze_wall.png)
    tile_types.push_back(TileType(collage.get_path(14), false, false, false, 0));  // ground (ground.png)
    tile_types.push_back(TileType(collage.get_path(13), false, false, false, 0));  // vertical (walk_way_shadow_vertical.png)
    tile_types.push_back(TileType(collage.get_path(15), false, false, false, 0));  // hole (maze_hole.png)
    tile_types.push_back(TileType(collage.get_path(16), false, false, false, 0));  // wooden floor (wooden_floor.png)
    tile_types.push_back(TileType(collage.get_path(18), false, false, false, 0));  // mushroom (mushroom.png)
    tile_types.push_back(TileType(collage.get_path(17), false, false, false, 0));  // test (test.png)
}

void TileManager::set_tile_texture(int tile_code, Tile& inspected_tile) {
    if (tile_code >= 0 && tile_code < tile_types.size()) {
        tile_types[tile_code].applyToTile(inspected_tile);
    } else {
        // Default texture if tile_code is not found
        tile_types[0].applyToTile(inspected_tile);  // Applying the first tile as a default
        // Optionally log or handle the invalid tile_code here
    }
}

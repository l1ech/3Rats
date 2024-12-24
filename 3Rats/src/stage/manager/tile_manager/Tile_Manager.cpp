#include <SDL2/SDL.h> // Include for SDL_Log
#include "Tile_Manager.h"

Tile_Manager::Tile_Manager()
{        
    width = Map_Constants::MAP_WIDTH;
    height = Map_Constants::MAP_HEIGHT;

    SDL_Log("[Tile_Manager]: Constructor called");
    
    // Initialize the tile types with their respective properties and textures
    tile_types.push_back(TileType(Texture_Constants::MAZE_DOOR, true, false, false, 0));  // end_door (maze_door.png)
    tile_types.push_back(TileType(Texture_Constants::WALK_WAY_SHADOW_HORIZONTAL, false, false, false, 0));  // horizontal (walk_way_shadow_horizontal.png)
    tile_types.push_back(TileType(Texture_Constants::MAZE_WALL, false, false, false, 1));  // wall (maze_wall.png)
    tile_types.push_back(TileType(Texture_Constants::GROUND, false, false, false, 0));  // ground (ground.png)
    tile_types.push_back(TileType(Texture_Constants::WALK_WAY_SHADOW_VERTICAL, false, false, false, 0));  // vertical (walk_way_shadow_vertical.png)
    tile_types.push_back(TileType(Texture_Constants::MAZE_HOLE, false, false, false, 0));  // hole (maze_hole.png)
    tile_types.push_back(TileType(Texture_Constants::WOODEN_FLOOR, false, false, false, 0));  // wooden floor (wooden_floor.png)
    tile_types.push_back(TileType(Texture_Constants::MUSHROOM, false, false, false, 0));  // mushroom (mushroom.png)
    tile_types.push_back(TileType(Texture_Constants::INTERACTABLE, false, false, false, 0));  // test (test.png)
}

void Tile_Manager::set_width(int width)
{
    this->width = width;
}

void Tile_Manager::set_height(int height)
{
    this->height = height;
}

void Tile_Manager::set_tile_texture(int tile_code, Tile& inspected_tile, SDL_Renderer* render_target) {
    SDL_Log("[Tile_Manager]: set_tile_texture called with tile_code=%d", tile_code);
    if (tile_code >= 0 && tile_code < tile_types.size()) {
        tile_types[tile_code].applyToTile(inspected_tile, render_target);
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Tile_Manager]: Error: Invalid tile code. Applying NO texture.");
    }
    SDL_Log("[Tile_Manager]: Finished setting texture for tile.");
}

void Tile_Manager::build_frame(std::vector<std::vector<int>>& data) {
    SDL_Log("[Tile_Manager]: build_frame called");
    for (int h = 0; h < height + 1; h++) {
        for (int w = 0; w < width + 1; w++) {
            if (w == 0 || w == width + 1 || h == 0 || h == height + 1) 
                data[h][w] = Tile_Constants::WALL;
            else 
                data[h][w] = Tile_Constants::SPACE;
        }
    }
}

void Tile_Manager::trim_boarder(std::vector<std::vector<int>>& data, std::vector<std::vector<int>>& map_data) {
    SDL_Log("[Tile_Manager]: trim_boarder called");
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            map_data[h][w] = data[h + 1][w + 1];
        }
    }
}

void Tile_Manager::set_textures(Tile* tile_array, std::vector<std::vector<std::pair<std::string, int>>> data, int TILE_SIZE, SDL_Renderer* render_target) {    
    SDL_Log("[Tile_Manager]: set_textures called");
    int total_tiles = height * width;
    int count = 0;

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            if (count % (total_tiles / 10) == 0) {
                SDL_Log("[Tile_Manager]: Tiles loaded (%d/%d)", count, total_tiles);
            }
            count++;

            Tile& inspected_tile = tile_array[get_tile(w, h)];

            int tile_code = orientation_to_tile_code(data[h][w].first);  // Use the string orientation to get the tile code
            if (tile_code != -1) {
                // If valid tile code, set the tile texture
                set_tile_texture(tile_code, inspected_tile, render_target);
            } else {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Tile_Manager]: Error: Invalid orientation, skipping tile.");
            }
            int x_cord = w * TILE_SIZE;
            int y_cord = h * TILE_SIZE;
            inspected_tile.set_cords(x_cord, y_cord);
        }
    }
    SDL_Log("[Tile_Manager]: All tiles loaded (%d/%d)", count, total_tiles);
}

int Tile_Manager::get_tile(int x, int y) { return y * width + x; }

int Tile_Manager::orientation_to_tile_code(const std::string& orientation) {
    if (orientation == "N") return 0;  // North - tile code 0
    if (orientation == "S") return 1;  // South - tile code 1
    if (orientation == "E") return 2;  // East - tile code 2
    if (orientation == "W") return 3;  // West - tile code 3
    return 4;  // Invalid orientation
}

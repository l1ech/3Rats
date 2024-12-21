#include <iostream> // Include for debugging messages
#include "Tile_Manager.h"

Tile_Manager::Tile_Manager()
{
}

Tile_Manager::Tile_Manager(int width, int height)
{
    this->width = width;
    this->height = height;

        

    std::cout << "[Tile_Manager]: Constructor called" << std::endl;
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
    std::cout << "[Tile_Manager]: set_tile_texture called with tile_code=" << tile_code << std::endl;
    if (tile_code >= 0 && tile_code < tile_types.size()) {
        tile_types[tile_code].applyToTile(inspected_tile, render_target);
    } else {
        std::cout << "[Tile_Manager]: Error: Invalid tile code. Applying NO texture." << std::endl;
    }
    std::cout << "[Tile_Manager]: Finished setting texture for tile." << std::endl;
}

void Tile_Manager::build_frame(std::vector<std::vector<int>>& data, int wall, int space) {
    std::cout << "[Tile_Manager]: build_frame called" << std::endl;
    for (int h = 0; h < height + 2; h++) {
        for (int w = 0; w < width + 2; w++) {
            if (w == 0 || w == width + 1 || h == 0 || h == height + 1) 
                data[h][w] = wall;
            else 
                data[h][w] = space;
        }
    }
}

void Tile_Manager::trim_boarder(std::vector<std::vector<int>>& data, std::vector<std::vector<int>>& map_data) {
    std::cout << "[Tile_Manager]: trim_boarder called" << std::endl;
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            map_data[h][w] = data[h + 1][w + 1];
        }
    }
}

void Tile_Manager::set_textures(Tile* tile_array, std::vector<std::vector<std::pair<int, int>>> data, int TILE_SIZE, SDL_Renderer* render_target) {    std::cout << "[Map]: set_textures called" << std::endl;
    //Texture_Manager texture_manager;
    int total_tiles = height * width;
    int count = 0;

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            if (count % (total_tiles / 10) == 0) {
                std::cout << "[Map]: Tiles loaded (" << count << "/" << total_tiles << ")" << std::endl;
            }
            count++;

            Tile& inspected_tile = tile_array[get_tile(w, h)];

            set_tile_texture(data[h][w].first, inspected_tile, render_target);

            int x_cord = w * TILE_SIZE;
            int y_cord = h * TILE_SIZE;
            inspected_tile.set_cords(x_cord, y_cord);
        }
    }
    std::cout << "[Map]: All tiles loaded (" << count << "/" << total_tiles << ")" << std::endl;
}

int Tile_Manager::get_tile(int x, int y) { return y * width + x; }

#pragma once

#include <vector>
#include <string>
//#include "../../../../core/Texture_Manager.h"
#include "Tile_Type.h"
#include "../../../Constants.h"

class Tile_Manager {
private:

    int width;
    int height;

    std::vector<TileType> tile_types;
    //Texture_Manager texture_manager;  // Add texture_manager instance to access texture paths

public:
    Tile_Manager();
    Tile_Manager(int width, int height);

    void set_width(int width);
    void set_height(int height);

    void set_tile_texture(int tile_code, Tile& inspected_tile, SDL_Renderer* render_target);
    
    void build_frame(std::vector<std::vector<int>>& data, int wall, int space);

    void trim_boarder(std::vector<std::vector <int>>& data, std::vector<std::vector <int>>& map_data);

    void set_textures(Tile* tile_array, std::vector<std::vector<std::pair<int, int>>> data, int TILE_SIZE, SDL_Renderer* render_target);

    int get_tile(int x, int y);
};

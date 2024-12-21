#pragma once

#include <string>
#include "Tile.h"
#include "SDL.h"

class TileType {
public:
    std::string texture_path;
    bool is_exit;
    bool is_hole;
    bool is_entrance;
    int height;

    // Constructor declaration with default arguments
    TileType(std::string texture, bool exit = false, bool hole = false, bool entrance = false, int h = 0);    

    void applyToTile(Tile& tile, SDL_Renderer* render_target) const;
};

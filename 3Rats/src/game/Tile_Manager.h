#pragma once

#include <vector>
#include <string>
#include "../core/Collage.h"
#include "Tile_Type.h"

class TileManager {
private:
    std::vector<TileType> tile_types;
    Collage collage;  // Add Collage instance to access texture paths

public:
    TileManager();

    void set_tile_texture(int tile_code, Tile& inspected_tile);
};

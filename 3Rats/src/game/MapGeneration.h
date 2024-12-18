#pragma once
#include <vector>
#include "Door.h"
#include "Tile.h"

class MapGenerator {
public:
    static void generate_maze(std::vector<std::vector<int>>& map_data, bool item_generation, bool entity_generation);
    static void generate_garden(std::vector<std::vector<int>>& map_data, bool item_generation, bool entity_generation);
    static void generate_cage(std::vector<std::vector<int>>& map_data, bool item_generation, bool entity_generation);

private:
    static void build_frame(std::vector<std::vector<int>>& map_data, int wall, int space);
    static void place_doors(std::vector<std::vector<int>>& map_data, Door* door_array);
    static void set_entities(std::vector<std::vector<int>>& map_data, bool entity_generation);
    static void set_items(std::vector<std::vector<int>>& map_data, bool item_generation);
};

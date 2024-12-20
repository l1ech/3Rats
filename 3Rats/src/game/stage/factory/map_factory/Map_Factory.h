// Map_Factory.h
#pragma once

#include "Map.h"   // Ensure this is the first include
#include <memory>  // For std::unique_ptr
#include "map_types/Maze_Map.h"
#include "map_types/Garden_Map.h"
#include "map_types/Cage_Map.h"

class Map_Factory {
public:
    enum class Map_Type { Maze, Garden, Cage };

    static std::unique_ptr<Map> createMap(Map_Type type);
};

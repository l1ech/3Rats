// Map_Factory.h
#pragma once

#include <memory>  // For std::unique_ptr
#include "Map.h"   // Include the base class first
#include "Maze_Map.h"  // Include the derived map types
#include "Garden_Map.h"
#include "Cage_Map.h"

class Map_Factory {
public:
    enum class Map_Type { Maze, Garden, Cage };

    static std::unique_ptr<Map> createMap(Map_Type type);
};

#include "Map_Factory.h"
#include "Maze_Map.h"
#include "Garden_Map.h"
#include "Cage_Map.h"

std::unique_ptr<Map> Map_Factory::createMap(Map_Type type) {
    switch (type) {
        case Map_Type::Maze:
            return std::make_unique<Maze_Map>();
        case Map_Type::Garden:
            return std::make_unique<Garden_Map>();
        case Map_Type::Cage:
            return std::make_unique<Cage_Map>();  // This requires the definition of the constructor
        default:
            return nullptr;  // Or handle unknown types
    }
}

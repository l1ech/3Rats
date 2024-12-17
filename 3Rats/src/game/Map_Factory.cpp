#include "Map_Factory.h"
#include <stdexcept>  // For std::invalid_argument

std::unique_ptr<Map> Map_Factory::createMap(Map_Type type)
{
switch (type) {
    case Map_Type::Maze:
        return std::make_unique<Maze_Map>();  // Ensure correct class name (case-sensitive)
    case Map_Type::Garden:
        return std::make_unique<Garden_Map>();
    case Map_Type::Cage:
        return std::make_unique<Cage_Map>();
    default:
        throw std::invalid_argument("Invalid map type");
    }
}

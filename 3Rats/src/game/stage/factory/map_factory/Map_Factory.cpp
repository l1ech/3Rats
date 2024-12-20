#include "Map_Factory.h"
#include "map_types/Maze_Map.h"
#include "map_types/Garden_Map.h"
#include "map_types/Cage_Map.h"

std::unique_ptr<Map> Map_Factory::createMap(Map_Type type) {
    std::cout << "[Map_Factory]: Creating map of type: " << static_cast<int>(type) << std::endl;
    switch (type) {
        case Map_Type::Maze:
            std::cout << "[Map_Factory]: Creating Maze_Map" << std::endl;
            return std::make_unique<Maze_Map>();
        case Map_Type::Garden:
            std::cout << "[Map_Factory]: Creating Garden_Map" << std::endl;
            return std::make_unique<Garden_Map>();
        case Map_Type::Cage:
            std::cout << "[Map_Factory]: Creating Cage_Map" << std::endl;
            return std::make_unique<Cage_Map>();  // This requires the definition of the constructor
        default:
            std::cerr << "[Map_Factory]: Unknown map type" << std::endl;
            return nullptr;
    }
}

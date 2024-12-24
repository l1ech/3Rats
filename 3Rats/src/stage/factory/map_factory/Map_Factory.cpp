#include "Map_Factory.h"
#include "map_types/Maze_Map.h"
#include "map_types/Garden_Map.h"
#include "map_types/Cage_Map.h"

std::unique_ptr<Map> Map_Factory::createMap(Map_Constants::Map_Type type) {
    SDL_Log("[Map_Factory]: Creating map of type: %d", static_cast<int>(type));

    switch (type) {
        case Map_Constants::Map_Type::Cage:
            SDL_Log("[Map_Factory]: Creating Cage_Map");
            return std::make_unique<Cage_Map>();  // This requires the definition of the constructor
        case Map_Constants::Map_Type::Maze:
            SDL_Log("[Map_Factory]: Creating Maze_Map");
            return std::make_unique<Maze_Map>();
        case Map_Constants::Map_Type::Garden:
            SDL_Log("[Map_Factory]: Creating Garden_Map");
            return std::make_unique<Garden_Map>();
        default:
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Map_Factory]: Unknown map type");
            return nullptr;
    }
}


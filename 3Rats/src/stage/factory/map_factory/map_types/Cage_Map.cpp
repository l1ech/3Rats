#include "Cage_Map.h"
#include <SDL.h>  // Required for SDL_Log and SDL_LogError

Cage_Map::Cage_Map()
{
}

void Cage_Map::generate(bool item_generation, bool entity_generation)
{
    SDL_Log("[Cage_Map]: Generating cage with width: %d and height: %d", width, height);

    try {
        SDL_Log("[Cage_Map]: Door_Manager created successfully.");

        int start_x = 1;
        int start_y = 1;

        int end_x = width;
        int end_y = height;

        // Generate doors with correct entry and exit directions
        SDL_Log("[Cage_Map]: Generating doors with entry direction: %d and exit direction: %d", entry_direction, exit_direction);
        door_manager.generate_doors(entry_direction, exit_direction, 2);

        door_manager.print_doors();

        std::vector<std::vector<int>> data(height + 2, std::vector<int>(width + 2));
        std::vector<std::vector<int>> map_data(height, std::vector<int>(width));
        std::vector<std::vector<int>> item_data(height, std::vector<int>(width));

        //print_vector(data, width, height);

        SDL_Log("[Cage_Map]: Initializing map data");
        
        tile_manager.build_frame(data);

        //print_vector(data, width, height);

        door_manager.place_doors(data);

        tile_manager.trim_boarder(data, map_data);

        //print_vector(map_data, width, height);

        if (item_generation) set_items_to_map(map_data, item_data, height, width, 20);  // Example probability

        SDL_Log("[Cage_Map]: Tries to generate Map #%d : %d", map_id, map_generation_try);
        SDL_Log("[Cage_Map]: saving data...");

        save_data(map_data, item_data);

        FileHandler file_handler;
        file_handler.saveMapToFile(map_data);

        //saveMapToFile(map_data);

    } catch (const std::exception& e) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Cage_Map]: Error during cage generation: %s", e.what());
    }
}

#include "Cage_Map.h"
#include <iostream>

Cage_Map::Cage_Map()
{
}

void Cage_Map::generate(bool item_generation, bool entity_generation)
{
    std::cout << "[Cage_Map]: Generating cage with width: " << width << " and height: " << height << std::endl;

    try {
        std::cout << "[Cage_Map]: Door_Manager created successfully." << std::endl;

        int start_x = 1;
        int start_y = 1;

        int end_x = width;
        int end_y = height;

        // Generate doors with correct entry and exit directions
        std::cout << "[Cage_Map]: Generating doors with entry direction: " << entry_direction << " and exit direction: " << exit_direction << std::endl;
        door_manager.generate_doors(entry_direction, exit_direction, 2);

        door_manager.print_doors();

        std::vector<std::vector<int>> data(height + 2, std::vector<int>(width + 2));
        std::vector<std::vector<int>> map_data(height, std::vector<int>(width));
        std::vector<std::vector<int>> item_data(height, std::vector<int>(width));

        std::cout << "[Cage_Map]: Initializing map data" << std::endl;
        
        tile_manager.build_frame(data, 9, 1);

        door_manager.place_doors(data);

        while (rec_pos(door_manager.get_doors()[0].get_x(), door_manager.get_doors()[0].get_y(), data, data[start_x][start_y]) != 0)
        {
            map_generation_try++;
            std::cout << "[Cage_Map]: Retrying to generate map #" << map_id << " : " << map_generation_try << std::endl;
        }
        tile_manager.trim_boarder(data, map_data);

        if (item_generation) set_items_to_map(map_data, item_data, height, width, 20);  // Example probability

        std::cout << "[Cage_Map]: Tries to generate Map #" << map_id << " : " << map_generation_try << std::endl;
        std::cout << "[Cage_Map]: saving data..." << std::endl;

        save_data(map_data, item_data);

    } catch (const std::exception& e) {
        std::cerr << "[Cage_Map]: Error during cage generation: " << e.what() << std::endl;
    }
}
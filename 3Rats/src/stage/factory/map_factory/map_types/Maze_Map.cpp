#include "Maze_Map.h"

Maze_Map::Maze_Map()
{
}

void Maze_Map::generate(bool item_generation, bool entity_generation)
{
    std::cout << "[Maze_Map]: Generating maze with width: " << width << " and height: " << height << std::endl;

    try {
        std::cout << "[Maze_Map]: Door_Manager created successfully." << std::endl;

        int start_x = 1;
        int start_y = 1;

        int end_x = width;
        int end_y = height;

        // Generate doors with correct entry and exit directions
        std::cout << "[Maze_Map]: Generating doors with entry direction: " << entry_direction << " and exit direction: " << exit_direction << std::endl;
        door_manager.generate_doors(entry_direction, exit_direction, 0);

        door_manager.print_doors();

        std::vector<std::vector<int>> data(height + 2, std::vector<int>(width + 2));
        std::vector<std::vector<int>> map_data(height, std::vector<int>(width));
        std::vector<std::vector<int>> item_data(height, std::vector<int>(width));

        std::cout << "[Maze_Map]: Initializing map data" << std::endl;

        tile_manager.build_frame(data);

        door_manager.place_doors(data);

        while (
            rec_pos(
                door_manager.get_doors()[0].get_x(), 
                door_manager.get_doors()[0].get_y(), 
                data, data[start_x][start_y]
            ) != Map_Constants::EXIT
        )
        {
            map_generation_try++;
            std::cout << "[Maze_Map]: Retrying to generate map #" << map_id << " : " << map_generation_try << std::endl;
        }

        tile_manager.trim_boarder(data, map_data);

        print_vector(data, width, height);

        if (item_generation) set_items_to_map(map_data, item_data, height, width, 30); // 80 meaning 1/80

        std::cout << "[Maze_Map]: Tries to generate Map #" << map_id << " : " << map_generation_try << std::endl;
        std::cout << "[Maze_Map]: saving data..." << std::endl;

        FileHandler file_handler;
        file_handler.saveMapToFile(map_data);

        // Print the generated map

        std::cout << "[Maze_Map]: Printing map data" << std::endl;
        print_vector(map_data, width, height);

    } catch (const std::exception& e) {
        std::cerr << "[Maze_Map]: Error during maze generation: " << e.what() << std::endl;
    }
}

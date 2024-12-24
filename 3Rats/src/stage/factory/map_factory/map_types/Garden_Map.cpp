#include "Garden_Map.h"

Garden_Map::Garden_Map()
{
}

void Garden_Map::generate(bool item_generation, bool entity_generation)
{
    std::cout << "[Garden_Map]: Generating garden with width: " << width << " and height: " << height << std::endl;

    int start_x = 1;
    int start_y = 1;

    int end_x = width;
    int end_y = height;

    // Generate doors with correct entry and exit directions
    std::cout << "[Garden_Map]: Generating doors with entry direction: " << entry_direction << " and exit direction: " << exit_direction << std::endl;

    try {
        door_manager.generate_doors(entry_direction, exit_direction, 1);
        std::cout << "[Garden_Map]: Doors generated successfully." << std::endl;

        std::cout << "[Garden_Map]: Door positions set successfully." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "[Garden_Map]: Error during door generation: " << e.what() << std::endl;
    }

    door_manager.print_doors();

    std::vector<std::vector<int>> data(height + 2, std::vector<int>(width + 2));
    std::vector<std::vector<int>> map_data(height, std::vector<int>(width));
    std::vector<std::vector<int>> item_data(height, std::vector<int>(width));
    std::vector<std::vector<int>> entity_data(height, std::vector<int>(width));

    std::cout << "[Garden_Map]: Initializing map data" << std::endl;

    tile_manager.build_frame(data);

    door_manager.place_doors(data);

    while (rec_pos(door_manager.get_doors()[0].get_x(), door_manager.get_doors()[0].get_y(), data, data[start_x][start_y]) != 0)
    {
        map_generation_try++;
        std::cout << "[Garden_Map]: Retrying to generate map #" << map_id << " : " << map_generation_try << std::endl;
    }

    tile_manager.trim_boarder(data, map_data);

    if (item_generation) set_items_to_map(map_data, item_data, height, width, 10);  // Example probability
    if (entity_generation) set_entity_to_map(map_data, entity_data, height, width, 70);  // Example probability

    std::cout << "[Garden_Map]: Tries to generate Map #" << map_id << " : " << map_generation_try << std::endl;
    std::cout << "[Garden_Map]: saving data..." << std::endl;

    FileHandler file_handler;
    file_handler.saveMapToFile(map_data);
    
    
    //print_vector(map_data, width, height);
}

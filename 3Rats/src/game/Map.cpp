#include "Map.h"

Map::Map()
{
    rec_iter = 0;
    width = 9;
    height = 6;
    item_id = 0;
    map_generation_try = 0;
}

void Map::set_type(int type) {
    const bool item_generation = true;
    const bool entity_generation = (type == 1);  // Example: GardenMap has entity generation

    // Your code using Map_Factory
    //std::unique_ptr<Map> new_map = Map_Factory::createMap(static_cast<Map_Factory::Map_Type>(type));


    switch (type) {
    case 0:
        std::cout << "Generating maze..." << std::endl;
        break;
    case 1:
        std::cout << "Generating garden..." << std::endl;
        break;
    case 2:
        std::cout << "Generating cage..." << std::endl;
        break;
    default:
        std::cout << "Invalid map type!" << std::endl;
        return;
    }

    std::cout << "Items generation: " << item_generation << std::endl;
    //new_map->generate(item_generation, entity_generation);
}


void Map::set_textures() {
    Collage collage;                  // Collage to manage texture paths
    TileManager tile_manager;         // TileManager instance
    const int TILE_SIZE = 64;         // Replace magic number with a constant
    int total_tiles = height * width; // Total tiles to process

    // Progress tracking variables
    int count = 0;

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            // Display progress for every 10% of tiles processed
            if (count % (total_tiles / 10) == 0) {
                std::cout << "Tiles loaded (" << count << "/" << total_tiles << ")" << std::endl;
            }
            count++;

            // Get references to the current tile and item
            Tile& inspected_tile = tile_array[get_tile(w, h)];
            Item& inspected_item = item_array[get_tile(w, h)];

            // Apply tile texture and properties using TileManager
            tile_manager.set_tile_texture(data[h][w].first, inspected_tile);

            // Compute coordinates for the tile
            int x_cord = w * TILE_SIZE;
            int y_cord = h * TILE_SIZE;

            // Apply item settings based on the second value in data
            if (data[h][w].second == 1) {
                inspected_item.set_on_map(true);
                inspected_item.set_cords(x_cord, y_cord);
                inspected_item.set_texture(collage.get_path(18)); // Mushroom texture
                item_id++;
            } else {
                inspected_item.set_on_map(false);
                inspected_item.set_cords(-100, -100); // Move off-map
                inspected_item.set_texture("");      // Clear texture
            }
        }
    }

    // Final progress output
    std::cout << "All tiles loaded (" << count << "/" << total_tiles << ")" << std::endl;
}


void Map::set_ptr(int* ptr)
{
    item_on_map = ptr;
}

void Map::set_map_id(int numer) { map_id = numer; }

void Map::set_layout(std::string layout)
{
    if (layout == "N")
    {
        entry_direction = 3;
        exit_direction = 1;
    }
    else if (layout == "E")
    {
        entry_direction = 3;
        exit_direction = 1;
    }
    else if (layout == "S")
    {
        entry_direction = 0;
        exit_direction = 2;
    }
    else if (layout == "W")
    {
        entry_direction = 0;
        exit_direction = 2;
    }
    else
    {
        std::cout << "error! the value is: " << layout << std::endl;
    }
}

void Map::set_entity_to_map(std::vector<std::vector<int>>& map_data, std::vector<std::vector<int>>& entity_data, int height, int width, int probability)
{

}

void Map::set_items_to_map(std::vector<std::vector<int>>& map_data, std::vector<std::vector<int>>& item_data, int height, int width, int probability)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map_data[i][j] == 0 || map_data[i][j] == 1 || map_data[i][j] == 2)
            {
                item_data[i][j] = 0;
            }
            else if (*item_on_map < item_array_size && random_ptr->roll_custom_dice(probability) == 1)
            {
                item_data[i][j] = 1;
                (*item_on_map)++;
            }
        }
    }
}

int Map::get_map_id() { return map_id; }

Door Map::get_door(int index) { return door_array[index]; }

int Map::get_hight() { return height; }

int Map::get_width() { return width; }

void Map::generate_maze(bool item_generation, bool entity_generation)
{
    //Door_Manager door_manager(width, height, random_ptr);

    int start_x = 1;
    int start_y = 1;

    int end_x = width;
    int end_y = height;

    //door_manager.generate_doors(entry_direction, exit_direction, 0);

    print_doors();

    std::vector<std::vector <int>> data(height + 2, std::vector<int>(width + 2));
    std::vector<std::vector <int>> map_data(height, std::vector<int>(width));
    std::vector<std::vector <int>> item_data(height, std::vector<int>(width));

    build_frame(data, 9, 1);

    place_doors(data, door_array);
    
    while (rec_pos(door_array[0].get_x(), door_array[0].get_y(), data, data[start_x][start_y]) != 0)
    { 
        map_generation_try++;
    }
    
    trim_boarder(data, map_data);

    //set_corners(map_data);

    if (item_generation) set_items_to_map(map_data, item_data, height, width, 30); // 80 meaning 1/80  

    std::cout << "Tries to generate Map #" << map_id << " : " << map_generation_try << std::endl;
    std::cout << "saving data..." << std::endl;

    save_data(map_data, item_data);
}

void Map::generate_garden(bool item_generation, bool entity_generation)
{
    //Door_Manager door_manager(width, height, random_ptr);    width = 9;

    height = 6;

    int start_x = 1;
    int start_y = 1;

    int end_x = width;
    int end_y = height;

    //door_manager.generate_doors(entry_direction, exit_direction, 1);

    print_doors();

    std::vector<std::vector <int>> data(height + 2, std::vector<int>(width + 2));    //x11; 0    y8; 0 means back one node
    std::vector<std::vector <int>> map_data(height, std::vector<int>(width));
    std::vector<std::vector <int>> item_data(height, std::vector<int>(width));
    std::vector<std::vector <int>> entity_data(height, std::vector<int>(width));

    build_frame(data, 1, 12);

    place_doors(data, door_array);

    trim_boarder(data, map_data);

    if (item_generation) set_items_to_map(map_data, item_data, height, width, 10);  //20 meaning 1/20

    if (entity_generation) set_entity_to_map(map_data, entity_data, height, width, 70);

    std::cout << "Tries to generate Map #" << map_id << " : " << map_generation_try << std::endl;

    std::cout << "saving data..." << std::endl;

    save_data(map_data, item_data);
}

void Map::generate_cage(bool item_generation, bool entity_generation)
{
    //Door_Manager door_manager(width, height, random_ptr);    
    width = 9;
    height = 6;

    int start_x = 1;
    int start_y = 1;

    int end_x = width;
    int end_y = height;

    //door_manager.generate_doors(entry_direction, exit_direction, 2);

    print_doors();
    
    std::pair<int, int> food_bowl = 
    { 
        random_ptr->roll_custom_dice(end_x), 
        random_ptr->roll_custom_dice(end_y) 
    };
    std::pair<int, int> bed = 
    { 
        random_ptr->roll_custom_dice(end_x), 
        random_ptr->roll_custom_dice(end_y) 
    };

    std::vector<std::vector <int>> data(height + 2, std::vector<int>(width + 2));    //x11; 0    y8; 0 means back one node
    std::vector<std::vector <int>> map_data(height, std::vector<int>(width));
    std::vector<std::vector <int>> item_data(height, std::vector<int>(width));

    // in this case it has to generate a hole. maybe not ?
    // maybe it generates a hole only if the player does an action?
    // for now for testing it is this

    build_frame(data, 1, 14);

    place_doors(data, door_array);

    data[food_bowl.second][food_bowl.first] = 15;
    data[bed.second][bed.first] = 16;


    trim_boarder(data, map_data);

    //if (item_generation) set_items_to_map(map_data, item_data, height, width, 70);  //20 meaning 1/20

    std::cout << "Tries to generate Map #" << map_id << " : " << map_generation_try << std::endl;
    std::cout << "saving data..." << std::endl;

    save_data(map_data, item_data);
}

int Map::rec_pos(int x, int y, std::vector<std::vector <int>>& arg, int& prev_direction)
{
    rec_iter++;
    int direction = ERROR_DIRECTION;

    //================= set new location
    // make this one structure a new function maybe???

    switch (random_ptr->roll_custom_dice(4))
    {
    case 1:
        direction = RIGHT;
        x++;
        break;

    case 2:
        direction = LEFT;
        x--;
        break;

    case 3:
        direction = UP;
        y++;
        break;

    case 4:
        direction = DOWN;
        y--;
        break;

    default:
        direction = ERROR_DIRECTION;
        std::cout << "ERROR: Direction is wrong." << std::endl;
        break;
    }

    //================= try new location

    int point_value = arg[y][x];

    if (point_value == 0)                         // finish or path
    {
        return point_value;
    }
    else if (point_value == 1)                    // empty field == wall
    {
        arg[y][x] = direction;

        int vall = rec_pos(x, y, arg, direction);

        if (vall == 0)
        {
            directions.push_back(direction);
            return vall;
        }
        else if (vall == 1)
        {

            arg[y][x] = direction;
        }
        else
        {
            arg[y][x] = 1;
            return vall;
        }
    }
    else
    {
        return point_value;
    }
    return -1;
}

void Map::build_frame(std::vector<std::vector<int>>& data, int wall, int space)
{
    for (int h = 0; h < height + 2; h++)
    {
        for (int w = 0; w < width + 2; w++)
        {
            if      (w == 0)            data[h][w] = wall;
            else if (w == width + 1)    data[h][w] = wall;
            else if (h == 0)            data[h][w] = wall;
            else if (h == height + 1)   data[h][w] = wall;
            else                        data[h][w] = space;
        }
    }
}

void Map::place_doors(std::vector<std::vector<int>>& data, Door* door_array)
{
    if (door_array[0].get_active())
        data[door_array[0].get_y()][door_array[0].get_x()] = 2;

    if (door_array[1].get_active())
        data[door_array[1].get_y()][door_array[1].get_x()] = 0;

    if (door_array[2].get_active())
        data[door_array[2].get_y()][door_array[2].get_x()] = 13;
}

void Map::print_vector(const std::vector<std::vector<int>>& arg, const int& size_x, const int& size_y)
{
    std::cout << "Vector: " << std::endl;

    for (const auto& row : arg) {
        for (const auto& element : row) {
            std::cout << element;
        }
        std::cout << '\n';
    }
}

void Map::print_doors()
{
    std::cout << "Entry: [" << door_array[0].get_x() << ";" << door_array[0].get_y() << "]" << std::endl;
    std::cout << "Exit: [" << door_array[1].get_x() << ";" << door_array[1].get_y() << "]" << std::endl;
    std::cout << "Hole: [" << door_array[2].get_x() << ";" << door_array[2].get_y() << "]" << std::endl;
}

void Map::trim_boarder(std::vector<std::vector <int>>& data, std::vector<std::vector <int>>& map_data)   //trim boarder
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            map_data[h][w] = data[h + 1][w + 1];
        }
    }
}
/*
void Map::set_corners(std::vector<std::vector<int>>& map_data)
{
    //make something smart here
}
*/

void Map::save_data(const std::vector<std::vector<int>>& map_data, const std::vector<std::vector<int>>& item_data)
{
    int i = 0;
    for (auto& row : data) {
        int j = 0;
        for (auto& cell : row) {
            cell.first = map_data[i][j];
            cell.second = item_data[i][j];
            j++;
        }
        i++;
    }
}

int Map::get_tile(int x, int y) { return y * width + x; }


#include "Map.h"
#include <iostream> // Include for debugging messages

Map::Map()
{
    std::cout << "[Map]: Constructor called" << std::endl;
    rec_iter = 0;
    width = 9;
    height = 6;
    //item_id = 0;
    map_generation_try = 0;
    tile_manager.set_width(width);
    tile_manager.set_height(height);

    door_manager.set_width(width);
    door_manager.set_height(height);   
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
        std::cout << "[Map]: error! the value is: " << layout << std::endl;
    }
}

void Map::set_entity_to_map(std::vector<std::vector<int>>& map_data, std::vector<std::vector<int>>& entity_data, int height, int width, int probability)
{
    std::cout << "[Map]: set_entity_to_map called" << std::endl;
    // Logic to set entities to map
}

void Map::set_items_to_map(std::vector<std::vector<int>>& map_data, std::vector<std::vector<int>>& item_data, int height, int width, int probability)
{
    std::cout << "[Map]: set_items_to_map called" << std::endl;
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

Door Map::get_door(int index)
{
    return door_manager.get_door(index);
}

void Map::set_random_ptr(Random* random_ptr)
{
    door_manager.set_random_ptr(random_ptr);
}

int Map::rec_pos(int x, int y, std::vector<std::vector<int>>& arg, int& prev_direction)
{
    std::cout << "[Map]: rec_pos called with x=" << x << ", y=" << y << std::endl;
    rec_iter++;
    if (rec_iter > MAX_RECURSION_DEPTH) {
        std::cerr << "[Map]: Maximum recursion depth reached. Backtracking." << std::endl;
        return -1;
    }

    std::cerr << "[Map]: Starting rec_pos: iteration=" << rec_iter 
              << ", x=" << x << ", y=" << y << ", prev_direction=" << prev_direction << std::endl;

    // Shuffle directions to ensure varied attempts
    std::vector<int> directions = {RIGHT, LEFT, UP, DOWN};
    std::shuffle(directions.begin(), directions.end(), std::default_random_engine(random_ptr->roll_custom_dice(4)));

    for (int dir : directions) {
        int new_x = x, new_y = y;

        // Update coordinates based on direction
        switch (dir) {
        case RIGHT: new_x++; break;
        case LEFT:  new_x--; break;
        case UP:    new_y--; break;
        case DOWN:  new_y++; break;
        default:
            std::cerr << "[Map]: Invalid direction chosen. Skipping." << std::endl;
            continue;
        }

        // Check bounds
        if (new_y < 0 || new_y >= arg.size() || new_x < 0 || new_x >= arg[0].size()) {
            std::cerr << "[Map]: Out of bounds: x=" << new_x << ", y=" << new_y << ". Skipping." << std::endl;
            continue;
        }

        // Fetch the value at the new position
        int point_value = arg[new_y][new_x];
        if (point_value == 9) 
        {
            std::cerr << "[Map]: Border detected at x=" << new_x << ", y=" << new_y << ". Skipping." << std::endl;
            continue;
        } 
        else if (point_value == 0) 
        {
            std::cerr << "[Map]: Path/finish found at x=" << new_x << ", y=" << new_y << std::endl;
            return 0;
        } 
        else if (point_value == 1) 
        {
            // Mark as visited
            arg[new_y][new_x] = dir;
            int result = rec_pos(new_x, new_y, arg, dir);
            if (result == 0) {
                return 0; // Found path
            }
            // Backtrack
            arg[new_y][new_x] = 1;
        } else if (point_value >= 3 && point_value <= 6) {
            std::cerr << "[Map]: Direction value detected at x=" << new_x << ", y=" << new_y << ". Continuing." << std::endl;
            continue;
        } else {
            std::cerr << "[Map]: Unexpected point_value=" << point_value 
                      << " at x=" << new_x << ", y=" << new_y << ". Skipping." << std::endl;
        }
    }

    std::cerr << "[Map]: Ending rec_pos at x=" << x << ", y=" << y << ", returning -1" << std::endl;
    return -1;
}

void Map::print_vector(const std::vector<std::vector<int>>& arg, const int& size_x, const int& size_y)
{
    std::cout << "[Map]: print_vector called" << std::endl;
    for (const auto& row : arg) {
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

void Map::save_data(const std::vector<std::vector<int>>& map_data, const std::vector<std::vector<int>>& item_data)
{
    std::cout << "[Map]: save_data called" << std::endl;
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

void Map::generate(bool item_generation, bool entity_generation) {
    std::cout << "[Map]: generate called with item_generation=" << item_generation << ", entity_generation=" << entity_generation << std::endl;
    // Map generation logic
}

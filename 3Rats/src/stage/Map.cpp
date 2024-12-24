#include "Map.h"
#include <iostream> // Include for debugging messages
#include "../core/Constants.h"

Map::Map() : width(Map_Constants::MAP_WIDTH), height(Map_Constants::MAP_HEIGHT)
{
    index = current_index++;
    name = "map";
    SDL_Log("[Map_%d](%s): Constructor called", index, name.c_str());

    rec_iter = 0;
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
    SDL_Log("[Map]: Setting layout to %s", layout.c_str());
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
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Map]: error! the value is: %s", layout.c_str());
    }
}

void Map::set_entity_to_map(std::vector<std::vector<int>>& map_data, std::vector<std::vector<int>>& entity_data, int height, int width, int probability)
{
    SDL_Log("[Map]: set_entity_to_map called");
    // Logic to set entities to map
}

void Map::set_items_to_map(std::vector<std::vector<int>>& map_data, std::vector<std::vector<int>>& item_data, int height, int width, int probability)
{
    SDL_Log("[Map]: set_items_to_map called");    
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
    this->random_ptr = random_ptr;
    door_manager.set_random_ptr(random_ptr);
}
int Map::rec_pos(int x, int y, std::vector<std::vector<int>> &arg, int &prev_direction)
{
    SDL_Log("[Map]: rec_pos called with position (%d, %d)", x, y);
    rec_iter++;
    if (rec_iter > Map_Constants::MAX_RECURSION_DEPTH) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Map]: Maximum recursion depth reached. Backtracking.");
        return -1;
    }

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Map]: Starting rec_pos: iteration=%d, x=%d, y=%d, prev_direction=%d",
                rec_iter, x, y, prev_direction);

    // Shuffle directions to ensure varied attempts
    std::vector<int> directions = {
        Map_Constants::RIGHT, 
        Map_Constants::LEFT, 
        Map_Constants::UP, 
        Map_Constants::DOWN
        };
    std::shuffle(
        directions.begin(), directions.end(), 
        std::default_random_engine(random_ptr->roll_custom_dice(4))
    );

    for (int dir : directions) {
        int new_x = x, new_y = y;

        // Update coordinates based on direction
        switch (dir) {
        case Map_Constants::RIGHT: new_x++; break;
        case Map_Constants::LEFT:  new_x--; break;
        case Map_Constants::UP:    new_y--; break;
        case Map_Constants::DOWN:  new_y++; break;
        default:
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[Map]: Invalid direction chosen: %d. Skipping.", dir);
            continue;
        }

        // Check bounds
        if (new_y < 0 || new_y >= arg.size() || new_x < 0 || new_x >= arg[0].size()) {
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[Map]: Out of bounds: x=%d, y=%d. Skipping.", new_x, new_y);
            continue;
        }

        // Fetch the value at the new position
        int point_value = arg[new_y][new_x];
        if (point_value == 9) {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Map]: Border detected at x=%d, y=%d. Skipping.", new_x, new_y);
            continue;
        } else if (point_value == 0) {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Map]: Path/finish found at x=%d, y=%d", new_x, new_y);
            return 0;
        } else if (point_value == 1) {
            // Mark as visited
            arg[new_y][new_x] = dir;
            int result = rec_pos(new_x, new_y, arg, dir);
            if (result == 0) {
                return 0; // Found path
            }
            // Backtrack
            arg[new_y][new_x] = 1;
        } else if (point_value >= 3 && point_value <= 6) {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Map]: Special direction value detected at x=%d, y=%d. Continuing.", new_x, new_y);
            continue;
        } else {
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[Map]: Unexpected point_value=%d at x=%d, y=%d. Skipping.", point_value, new_x, new_y);
        }
    }

    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[Map]: Ending rec_pos at x=%d, y=%d, returning -1", x, y);
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
    SDL_Log("[Map]: save_data called");
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
    // Pure virtual function
}
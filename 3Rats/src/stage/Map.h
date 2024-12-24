#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>  // Required for std::ofstream
#include <iostream>
#include <sstream>  // Add this header


#include "../core/Body.h"
//#include "../../../../core/Texture_Manager.h"

#include "Door.h"
#include "Tile.h"
#include "Item.h"


#include "manager/door_manager/Door_Manager.h"
#include "manager/tile_manager/Tile_Manager.h"
//#include "manager/item_manager/Item_Manager.h"

#include "manager/map_manager/Level_Structure.h"


#include "handler/file_handler/FileHandler.h"

class Map : public Level_Structure
{
private:

    Random* random_ptr;
    // Constants for recursion and directions
    
    // Member variables
    //int item_id;
    int* item_on_map;
    //double time;
    int rec_iter;
    
    std::vector<int> directions;
    //std::vector<std::vector<std::vector<std::vector<int>>>> hyper_map;
    
    std::pair<int, int> data[6][9];

    // Functions for map generation
    //int get_tile(int x, int y);

public:
    Tile_Manager tile_manager;
    Door_Manager door_manager;

    int index;
	static int current_index;	
	std::string name;

    // Member variables
    int width;
    int height;
    
    //Door door_array[3];
    int map_id;
    int map_generation_try;
    int entry_direction;
    int exit_direction;

    // Recursion function
    int rec_pos(int x, int y, std::vector<std::vector<int>>& arg, int& prev_direction);

    // Helper functions for visualization and data management
    void print_vector(const std::vector<std::vector<int>>& arg, const int& size_x, const int& size_y);
    void save_data(const std::vector<std::vector<int>>& map_data, const std::vector<std::vector<int>>& item_data);

    // Functions for adding entities and items to the map
    void set_entity_to_map(std::vector<std::vector<int>>& map_data, std::vector<std::vector<int>>& entity_data, int height, int width, int probability);
    void set_items_to_map(std::vector<std::vector<int>>& map_data, std::vector<std::vector<int>>& item_data, int height, int width, int probability);

    // Pure virtual function for generating the map
    virtual void generate(bool item_generation, bool entity_generation) = 0; // Pure virtual function

    // Constructor and Destructor
    Map();
    virtual ~Map() = default;

    // Setters
    void set_ptr(int* ptr);
    void set_map_id(int number);
    void set_layout(std::string layout);

    // Getters
    int get_map_id();
    //int get_width();
    Door get_door(int index);
    void set_random_ptr(Random* random_ptr);
};

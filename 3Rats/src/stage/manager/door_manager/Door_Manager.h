#pragma once

#include "../../Door.h"
#include "../../../core/Random.h"

#include <vector>
#include <iostream>

class Door_Manager
{
private:
    std::vector<Door> doors;    
    Random* random_ptr;            
    int width;                        
    int height;                       
public:
    Door_Manager();
    Door_Manager(int width, int height, Random* random_ptr);
    ~Door_Manager();

    void set_width(int width);
    void set_height(int height);
    void set_random_ptr(Random* random_ptr);

    // Methods to generate doors
    void generate_door(
        int direction, 
        int index, 
        int type, 
        bool active
        );

    void generate_doors(
        int entry_direction, 
        int exit_direction, 
        int type_generation
        );

    // Optionally, getters for accessing private data
    std::vector<Door>& get_doors();
    Random* get_random_ptr();
    int get_width() const;
    int get_height() const;

    void print_doors();
    void place_doors(std::vector<std::vector<int>>& data);

    Door get_door(int index);


};


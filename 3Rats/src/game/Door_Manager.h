#pragma once

#include "Door.h"
#include "../core/Random.h"

#include <vector>
#include <iostream>

class Door_Manager
{
private:
    // Store door configurations or any other internal states
    std::vector<Door> doors;         // To hold a collection of Door objects
    Random* random_ptr;              // Random object pointer for randomization

    int width;                        // Width of the area (for door placement)
    int height;                       // Height of the area (for door placement)

public:
    // Constructor that initializes the data and stores necessary info
    Door_Manager(int width, int height, Random* random_ptr);

    // Destructor
    ~Door_Manager();

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
};


#pragma once
#include "../Map.h"  // Include the base class
#include "../../../manager/door_manager/Door_Manager.h"

class Maze_Map : public Map {
public:
    Maze_Map();
    void generate(bool item_generation, bool entity_generation) override;
};
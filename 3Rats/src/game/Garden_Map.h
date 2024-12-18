#pragma once
#include "Map.h"  // Include the base class

class Garden_Map : public Map {
public:
    Garden_Map();
    void generate(bool item_generation, bool entity_generation) override;
};

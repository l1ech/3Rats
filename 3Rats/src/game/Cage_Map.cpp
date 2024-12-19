#include "Cage_Map.h"
#include <iostream>

Cage_Map::Cage_Map() {
    // Constructor implementation (if any specific initialization is needed)
    std::cout << "Cage_Map created!" << std::endl;
}

void Cage_Map::generate(bool item_generation, bool entity_generation) {
    generate_cage(item_generation, entity_generation);
}

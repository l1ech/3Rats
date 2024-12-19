#include "Maze_Map.h"

Maze_Map::Maze_Map()
{
}

void Maze_Map::generate(bool item_generation, bool entity_generation)
{
    generate_maze(item_generation, entity_generation);
}

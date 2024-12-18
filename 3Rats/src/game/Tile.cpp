#include "Body.h"
#include <memory>
#include "Tile.h"
#include "../core/Collage.h"

Tile::Tile()
{
    Collage collage;

    is_entrance = false;
    is_exit = false;
    is_hole = false;

    file_path = collage.get_path(2);

    std::cout << "Tile constructor: Created tile with path: " << file_path << std::endl;
}

Tile::Tile(const Tile& other)
{
    std::cout << "Tile copy constructor: Copying tile with file_path: " << other.file_path << std::endl;
    
    is_exit = other.is_exit;
    is_entrance = other.is_entrance;
    is_hole = other.is_hole;
    this->hight = other.hight;

    this->file_path = other.file_path;
    this->ptr_renderer = other.ptr_renderer;

    std::cout << "Tile <Copy>: Set hight: " << this->hight << ", Entrance: " << this->is_entrance 
              << ", Exit: " << this->is_exit << ", Hole: " << this->is_hole << std::endl;

    // Call the methods to set surface, texture, and coordinates
    set_surface(other.ptr_renderer);
    set_texture(other.file_path);
    set_cords(other.origin_x, other.origin_y);
}

Tile::~Tile()
{
    // Log when the destructor is called, can help track if the object is being destroyed properly
    std::cout << "Tile destructor: Destroying tile with file_path: " << file_path << std::endl;
}


#include "../../../Body.h"
#include <memory>
#include "Tile.h"
//#include "../../../../core/Texture_Manager.h"

Tile::Tile()
{
    //Texture_Manager texture_manager;

    is_entrance = false;
    is_exit = false;
    is_hole = false;

    //file_path = texture_manager.get_path(2);
    file_path = Texture_Constants::META_TEXTURE;

    std::cout << "[tile]: Tile constructor: Created tile with path: " << file_path << std::endl;
}

Tile::Tile(const Tile& other)
{
    std::cout << "[tile]: Tile copy constructor: Copying tile with file_path: " << other.file_path << std::endl;
    
    is_exit = other.is_exit;
    is_entrance = other.is_entrance;
    is_hole = other.is_hole;
    this->hight = other.hight;
    this->name = other.name;

    this->file_path = other.file_path;
    this->ptr_renderer = other.ptr_renderer;

    std::cout << "[tile]: Tile <Copy>: Set hight: " << this->hight << ", Entrance: " << this->is_entrance 
              << ", Exit: " << this->is_exit << ", Hole: " << this->is_hole << std::endl;

    // Call the methods to set surface, texture, and coordinates
    set_surface(other.ptr_renderer);
    set_texture(other.file_path);
    set_cords(other.origin_x, other.origin_y);
}

Tile::~Tile()
{
    // Log when the destructor is called, can help track if the object is being destroyed properly
    std::cout << "[tile]: Tile destructor: Destroying tile with file_path: " << file_path << std::endl;
}


void Tile::draw(SDL_Renderer* render_tatget) const
{
    std::cout << "[tile]: Tile draw called" << std::endl;
    Body::draw(render_tatget);
}

Tile& Tile::operator=(const Tile& other)
{
    if (this != &other) // Check for self-assignment
    {
        Body::operator=(other); // Call the base class assignment operator

        // Copy members
        is_exit = other.is_exit;
        is_entrance = other.is_entrance;
        is_hole = other.is_hole;

        // Deep copy for dynamic members
        // Example: 
        // delete data; // Free existing resource
        // data = new int(*other.data);
    }
    return *this;
}

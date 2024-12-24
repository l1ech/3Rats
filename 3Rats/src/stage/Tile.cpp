#include "../core/Body.h"
#include <memory>
#include "Tile.h"

Tile::Tile()
{
    //Texture_Manager texture_manager;

    is_entrance = false;
    is_exit = false;
    is_hole = false;

    file_path = Texture_Constants::META_TEXTURE;

    SDL_Log("[Tile]: Tile constructor: Created tile with path: %s", file_path.c_str());
}

Tile::Tile(const Tile& other)
{
    SDL_Log("[Tile]: Tile copy constructor: Copying tile with file_path: %s", file_path.c_str());

    is_exit = other.is_exit;
    is_entrance = other.is_entrance;
    is_hole = other.is_hole;
    this->hight = other.hight;
    this->name = other.name;

    this->file_path = other.file_path;
    this->ptr_renderer = other.ptr_renderer;

    SDL_Log("[Tile]: Tile <Copy>: Set height: %d, Entrance: %d, Exit: %d, Hole: %d", this->hight, this->is_entrance, this->is_exit, this->is_hole);

    // Call the methods to set surface, texture, and coordinates
    set_surface(other.ptr_renderer);
    set_texture_path(other.file_path);
    set_cords(other.origin_x, other.origin_y);
}

Tile::~Tile()
{
    // Log when the destructor is called, can help track if the object is being destroyed properly
    SDL_Log("[Tile]: Tile destructor: Destroying tile with file_path: %s", file_path.c_str());
}


void Tile::draw(SDL_Renderer* render_tatget) const
{
    //SDL_Log("[Tile]: Tile draw called");
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

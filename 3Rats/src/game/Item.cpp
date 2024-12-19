#include "Item.h"

Item::Item()
{
	is_on_map = false;
	is_picked_up = false;
}

Item::~Item()
{
	SDL_DestroyTexture(texture);
}
	
//void Item::Update(float delta) { }

void Item::Draw(SDL_Renderer* renderTarget)
{
	SDL_RenderCopy(renderTarget, texture, &crop_rect, &position_rect);
}

bool Item::get_on_map() { return is_on_map; }

void Item::set_on_map(bool value) { is_on_map = value; }

void Item::set_pick_up(bool value)
{
	is_picked_up = value;
}

bool Item::get_pick_up()
{
	return is_picked_up;
}


// Copy constructor
Item::Item(const Item& other) : Body(other) // Call the base class copy constructor
{
    is_on_map = other.is_on_map;
    is_picked_up = other.is_picked_up;
    weight = other.weight;
}

// Copy assignment operator
Item& Item::operator=(const Item& other)
{
    if (this != &other) {
        Body::operator=(other); // Call the base class assignment operator
        is_on_map = other.is_on_map;
        is_picked_up = other.is_picked_up;
        weight = other.weight;
    }
    return *this;
}


#include "Prop.h"

Prop::Prop()
{
	is_on_map = false;
	is_picked_up = false;
}

Prop::~Prop()
{
	SDL_DestroyTexture(texture);
}
	
//void Prop::Update(float delta) { }

void Prop::Draw(SDL_Renderer* renderTarget)
{
	SDL_RenderCopy(renderTarget, texture, &crop_rect, &position_rect);
}

bool Prop::get_on_map() { return is_on_map; }

void Prop::set_on_map(bool value) { is_on_map = value; }

void Prop::set_pick_up(bool value)
{
	is_picked_up = value;
}

bool Prop::get_pick_up()
{
	return is_picked_up;
}



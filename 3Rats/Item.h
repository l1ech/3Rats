#pragma once	

#include "Body.h"

class Item : public Body
{
private:
	bool is_on_map;
	bool is_picked_up;

public:
	Item();
	~Item();

	//void Update(float delta);
	void Draw(SDL_Renderer* renderTarget);

	bool get_on_map();
	void set_on_map(bool value);

	bool get_pick_up();
	void set_pick_up(bool value);


};
#pragma once

#include "../../../Body.h"

class Tile : public Body
{
private:

public:
	Tile();
	Tile(const Tile& other);
	Tile& operator=(const Tile& other);
	~Tile();

	void draw(SDL_Renderer* render_tatget);

	bool is_exit;
	bool is_entrance;
	bool is_hole;

};
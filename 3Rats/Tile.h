#pragma once

#include "Body.h"

class Tile : public Body
{
private:

public:
	Tile();

	bool is_exit, is_entrance, is_hole;

};
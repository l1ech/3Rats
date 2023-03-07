#pragma once

#include "Body.h"

class Tile : public Body
{
private:

public:
	Tile();

	bool is_exit;
	bool is_entrance;
	bool is_hole;

};
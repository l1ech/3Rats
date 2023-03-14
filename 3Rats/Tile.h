#pragma once

#include "Body.h"

class Tile : public Body
{
private:

public:
	Tile();
	Tile(bool exit, bool entrance, bool hole, std::string path, int height);

	bool is_exit;
	bool is_entrance;
	bool is_hole;

};
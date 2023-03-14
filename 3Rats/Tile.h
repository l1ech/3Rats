#pragma once

#include "Body.h"

class Tile : public Body
{
private:

public:
	Tile();
	Tile(const Tile& other);
	Tile(bool exit, bool entrance, bool hole, std::string path, int height);
	
	~Tile();

	//Tile& operator=(Tile rhs);

	bool is_exit;
	bool is_entrance;
	bool is_hole;

};
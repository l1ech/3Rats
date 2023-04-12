#pragma once

#include "Body.h"

class Mop
{
private:

public:
	Mop();

	struct block_direction_counter {
		int right;
		int left;
		int up;
		int down;
	};

	struct block_direction {
		bool right;
		bool left;
		bool up;
		bool down;
	};

	struct player_move
	{
		bool up;
		bool down;
		bool left;
		bool right;
	};


};
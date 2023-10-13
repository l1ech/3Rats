#pragma once

#include "Body.h"
#include "Random.h"

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


	float moveSpeed;
	bool is_moving;
	int current_direction;

	bool dead;

	Random* random_ptr;


};
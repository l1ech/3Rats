#pragma once

#include<vector>
#include <iostream>
#include <string>
#include <tuple>
#include <SDL.h>

#include"Item.h"



class Controller {
protected:

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

	struct acteur_move
	{
		bool up;
		bool down;
		bool left;
		bool right;
	};
};

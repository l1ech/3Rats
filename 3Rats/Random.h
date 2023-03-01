#pragma once

#include <random>

class Random
{
public:
	bool flip_coin();
	int roll_dice();
	int roll_custom_dice(int num);
};
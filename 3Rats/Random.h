#pragma once

#include <random>

class Random
{
private:
	typedef std::mt19937 MyRNG;  // the Mersenne Twister with a popular choice of parameters
	uint32_t seed_val;           // populate somehow
	MyRNG rng;                   // e.g. keep one global instance (per thread)
public:

	Random(uint32_t seed_val);
	Random();					// this constructor allways starts with the same 
								// seed = 1

	bool flip_coin();
	int roll_dice();
	int roll_custom_dice(int num);
};
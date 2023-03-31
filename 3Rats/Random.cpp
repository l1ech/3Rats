//  this code wasent made by me. 
//  i copied it from here:
//  https://stackoverflow.com/a/13445752/18288994

#include "Random.h"

Random::Random(uint32_t seed_val_parameter)
{
    seed_val = seed_val_parameter;
    rng.seed(seed_val);
}

bool Random::flip_coin()
{
    std::uniform_int_distribution<uint32_t> uint_dist(0, 1); // range [0,1]
    return uint_dist(rng);
}

int Random::roll_dice()
{
    std::uniform_int_distribution<uint32_t> uint_dist(1, 6); // range [1,6]
    return uint_dist(rng);
}

int Random::roll_custom_dice(int num)
{
    std::uniform_int_distribution<uint32_t> uint_dist(1, num); // range [1,num]
    return uint_dist(rng);
}

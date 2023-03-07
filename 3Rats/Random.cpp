//  this code wasent made by me. 
//  i copied it from here:
//  https://stackoverflow.com/a/13445752/18288994

#include "Random.h"

bool Random::flip_coin()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist1(0, 1);

    return dist1(rng);
}

int Random::roll_dice()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist1(1, 6);

    return dist1(rng);
}

int Random::roll_custom_dice(int num)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist1(1, num);

    return dist1(rng);
}

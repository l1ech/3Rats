#include "Player_Computer.h"

Player_Computer::Player_Computer()
{
}

Player_Computer::~Player_Computer()
{
    std::cout << "[Player_Computer<" << index << ">]: Destructor called" << std::endl;
    SDL_DestroyTexture(texture);
}

void Player_Computer::Update(float delta, const Uint8 *keyState, int mode, Acteur &p1)
{
}
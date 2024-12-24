#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
    std::cout << "[Enemy<" << index << ">]: Destructor called" << std::endl;
    SDL_DestroyTexture(texture);

}

void Enemy::Update(float delta, const Uint8 *keyState, int mode, Acteur &p1)
{
}
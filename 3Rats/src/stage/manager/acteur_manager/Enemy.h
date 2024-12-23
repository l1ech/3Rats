#pragma once

#include "Acteur.h"

class Enemy : public Acteur
{
private:
    /* data */
public:
    Enemy(/* args */);
    ~Enemy();

    void Update(float delta, const Uint8* keyState, int mode, Acteur& p1) override;

};
#pragma once

#include "Acteur.h"

class Player : public Acteur
{
private:
    /* data */
public:
    Player();
    ~Player();
    void Update(float delta, const Uint8* keyState, int mode, Acteur& p1) override;
};

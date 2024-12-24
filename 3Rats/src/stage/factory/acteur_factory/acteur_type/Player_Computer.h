#pragma once

#include "../../../Acteur.h"

class Player_Computer : public Acteur
{
private:
    /* data */
public:
    Player_Computer(/* args */);
    ~Player_Computer(); 

    void Update(float delta, const Uint8* keyState, int mode, Acteur& p1) override;
};

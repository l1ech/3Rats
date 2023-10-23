#pragma once

#include "Text.h"

class Button : public Text
{
public:
    Button(SDL_Renderer* renderer, int x, int y, int width, int height);

    void render();
    void handleEvent(const SDL_Event& event);
    
    bool get_clicked();

private:
    Button();

    SDL_Renderer* renderer;
    SDL_Rect rect;
    bool clicked;


};

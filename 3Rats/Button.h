#pragma once

#include "Text.h"

#include <SDL.h>

class Button : public Text
{
public:
    Button(SDL_Renderer* renderer, int x, int y, int width, int height);

    void render();
    void handleEvent(const SDL_Event& event);

private:
    SDL_Renderer* renderer;
    SDL_Rect rect;
    bool clicked;
};

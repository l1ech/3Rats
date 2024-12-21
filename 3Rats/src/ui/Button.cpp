#include "Button.h"
#include <iostream>

Button::Button(SDL_Renderer* renderer, int x, int y, int width, int height)
    : renderer(renderer), rect({ x, y, width, height }), clicked(false) 
{
    std::cout << "[Button]: Button created at (" << x << ", " << y << ") with size (" << width << ", " << height << ")" << std::endl;
}

void Button::render() 
{
    if (clicked) 
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green when clicked
        std::cout << "[Button]: Button rendered as clicked (green)" << std::endl;
    }
    else 
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red when not clicked
        std::cout << "[Button]: Button rendered as not clicked (red)" << std::endl;
    }
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

void Button::handleEvent(const SDL_Event& event) 
{
    if (event.type == SDL_MOUSEBUTTONDOWN) 
    {
        int mouseX = event.button.x;
        int mouseY = event.button.y;
        std::cout << "[Button]: Mouse button down at (" << mouseX << ", " << mouseY << ")" << std::endl;

        if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
            mouseY >= rect.y && mouseY <= rect.y + rect.h) 
        {
            clicked = !clicked; // Toggle button state
            std::cout << "[Button]: Button state toggled to " << (clicked ? "clicked" : "not clicked") << std::endl;
            //render();
        }
    }
}

Button::Button()
{
    std::cout << "[Button]: Default constructor called" << std::endl;
}

bool Button::get_clicked()
{
    std::cout << "[Button]: get_clicked called, returning " << clicked << std::endl;
    return clicked;
}

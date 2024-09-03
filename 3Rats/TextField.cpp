#include "TextField.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <cstdio>

// Default constructor
TextField::TextField()
    : mRenderer(nullptr), mFont(nullptr), mRect{ 0, 0, 100, 30 }, mText(""), mTextColor{ 0, 0, 0, 255 }, mTexture(nullptr), mVisible(true)
{
    // Optionally, initialize SDL text input here
    SDL_StartTextInput();
}

// Parameterized constructor
TextField::TextField(SDL_Renderer* renderer, TTF_Font* font, int x, int y, int w, int h)
    : mRenderer(renderer), mFont(font), mRect{ x, y, w, h }, mText(""), mTextColor{ 0, 0, 0, 255 }, mTexture(nullptr), mVisible(true)
{
    // Optionally, initialize SDL text input here
    SDL_StartTextInput();
}

// Destructor
TextField::~TextField()
{
    // Destroy the texture if it exists
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
    }

    // Stop SDL text input
    SDL_StopTextInput();
}

// Handle keyboard and text input events
void TextField::handleEvent(SDL_Event* e)
{
    if (!mVisible) return;

    if (e->type == SDL_KEYDOWN)
    {
        if (e->key.keysym.sym == SDLK_BACKSPACE && !mText.empty())
        {
            mText.pop_back();
            renderText();
        }
        else if (e->key.keysym.sym == SDLK_RETURN)
        {
            // Handle the "send" event here
        }
        else if (e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
        {
            SDL_SetClipboardText(mText.c_str());
        }
        else if (e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
        {
            mText = SDL_GetClipboardText();
            renderText();
        }
    }
    else if (e->type == SDL_TEXTINPUT)
    {
        if (!(SDL_GetModState() & KMOD_CTRL && (e->text.text[0] == 'c' || e->text.text[0] == 'C' || e->text.text[0] == 'v' || e->text.text[0] == 'V')))
        {
            mText += e->text.text;
            renderText();
        }
    }
}// Render the text field and the input text
void TextField::render()
{
    if (!mVisible) return;

    // Create a background rectangle with a fixed width of 600 (full screen width)
    SDL_Rect backgroundRect = { mRect.x, mRect.y, 600, mRect.h };

    // Draw black background across the full width of the screen
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255); // Black color
    SDL_RenderFillRect(mRenderer, &backgroundRect);  // Fill the rectangle

    // Render the text on top of the black background
    if (mTexture != nullptr) {
        SDL_RenderCopy(mRenderer, mTexture, nullptr, &mRect);
    }
}

// Update the text texture
void TextField::renderText()
{
    // Destroy the previous texture if it exists
    if (mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
    }

    // Return if there's no text to render
    if (mText.empty()) {
        return;
    }

    // Set text color to white
    mTextColor = { 255, 255, 255, 255 }; // White color

    // Create surface with white text
    SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, mText.c_str(), mTextColor);
    if (textSurface == nullptr) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    // Create texture from the surface
    mTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
    if (mTexture == nullptr) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }

    // Update the rectangle dimensions to match the text size (only height is updated)
    mRect.w = textSurface->w;  // Width of the text
    mRect.h = textSurface->h;  // Height of the text

    // Free the surface
    SDL_FreeSurface(textSurface);
}


// Set the text programmatically
void TextField::setText(const std::string& text)
{
    mText = text;
    renderText();
}

// Get the current text
std::string TextField::getText() const
{
    return mText;
}

// Set visibility of the text field
void TextField::setVisible(bool visible)
{
    mVisible = visible;
    if (!mVisible && mTexture != nullptr) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
    }
}

// Get visibility state of the text field
bool TextField::isVisible() const
{
    return mVisible;
}

// Set the text color
void TextField::setTextColor(SDL_Color color)
{
    mTextColor = color;
    renderText();
}

// Set the renderer
void TextField::setRenderer(SDL_Renderer* renderer)
{
    mRenderer = renderer;
}

// Set the font
void TextField::setFont(TTF_Font* font)
{
    mFont = font;
    renderText();
}

// Get the renderer
SDL_Renderer* TextField::getRenderer() const
{
    return mRenderer;
}

// Get the font
TTF_Font* TextField::getFont() const
{
    return mFont;
}

// Set the position of the text field
void TextField::setPosition(int x, int y)
{
    mRect.x = x;
    mRect.y = y;
    renderText(); // Update the text rendering if needed
}

// Set the size of the text field
void TextField::setSize(int w, int h)
{
    mRect.w = w;
    mRect.h = h;
    renderText(); // Update the text rendering if needed
}

void TextField::set_m_rect(int x, int y, int w, int h)
{
    mRect.x = x;
    mRect.y = y;
    mRect.w = w;
    mRect.h = h;
}

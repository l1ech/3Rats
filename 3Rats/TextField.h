#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class TextField {
public:
    TextField();
    TextField(SDL_Renderer* renderer, TTF_Font* font, int x, int y, int w, int h);
    ~TextField();

    void handleEvent(SDL_Event* e);
    void render();

    void setText(const std::string& text);
    std::string getText() const;

    void setVisible(bool visible);
    bool isVisible() const;

    void setTextColor(SDL_Color color);

    void setRenderer(SDL_Renderer* renderer);
    void setFont(TTF_Font* font);

    void setPosition(int x, int y);
    void setSize(int w, int h);

    void set_m_rect(int x, int y, int w, int h);

    SDL_Renderer* getRenderer() const;
    TTF_Font* getFont() const;

private:
    void renderText();

    SDL_Renderer* mRenderer;
    TTF_Font* mFont;
    SDL_Rect mRect;
    std::string mText;
    SDL_Color mTextColor;
    SDL_Texture* mTexture;
    bool mVisible;
};

#endif // TEXTFIELD_H

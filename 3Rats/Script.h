#ifndef CHAT_H
#define CHAT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <iostream>
#include "TextField.h" // Include the header file for TextField
#include "Inspector.h"
#include "Acteur.h"

class Script {
public:
    Script();
    Script(SDL_Renderer* renderer, TTF_Font* font, int x, int y, int w, int h);
    ~Script();

    // Set methods
    void setRenderer(SDL_Renderer* renderer);
    void setFont(TTF_Font* font);
    void setPosition(int x, int y);
    void setSize(int w, int h);
    void setVisible(bool visible);

    void handleEvent(const SDL_Event& e);
    void render();
    void toggleVisibilityChat();
    bool isVisible() const;
    void join(Acteur* a); // in the future make this a templet so that all can join
    void add_inspector(Inspector* inspector);
    Inspector* get_inspector();

    std::string pop_message();

    bool message_alert();


private:
    void sendMessage();
    void renderMessages();

    // Member variables
    TextField mTextField;                           // Text field for input
    SDL_Rect mMessageArea;                          // Rectangle defining the area for displaying messages
    std::vector<std::string> mMessages;             // Vector to store script messages
    bool mVisible;                                  // Flag to indicate if the script is visible
    
    std::vector<Acteur*> active_users;
    Inspector* inspector;

};

#endif // CHAT_H

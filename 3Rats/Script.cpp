#include "Script.h"

// Default constructor
Script::Script()
    : mTextField(),                  // Use the default constructor of TextField
    mMessageArea{ 100, 100, 100, 100 },     // Initialize SDL_Rect with default values
    mMessages(),                    // Initialize empty vector
    mVisible(false)                 // Default visibility is false
{
    // Optionally, you can set default values or perform additional initialization here
}

// Parameterized constructor
Script::Script(SDL_Renderer* renderer, TTF_Font* font, int x, int y, int w, int h)
    : mTextField(renderer, font, x, y, w, h), // Initialize TextField with provided parameters
    mMessageArea{ x, y, w, h },             // Initialize SDL_Rect with provided values
    mMessages(),                         // Initialize empty vector
    mVisible(false)                       // Default visibility is true
{
    // Additional initialization if needed
}

// Destructor
Script::~Script() {
    // Cleanup code if necessary
}

// Set methods
void Script::setRenderer(SDL_Renderer* renderer) {
    mTextField.setRenderer(renderer);
}

void Script::setFont(TTF_Font* font) {
    mTextField.setFont(font);
}

void Script::setPosition(int x, int y) {
    mMessageArea.x = x;
    mMessageArea.y = y;
    mTextField.setPosition(x, y);
}

void Script::setSize(int w, int h) {
    mMessageArea.w = w;
    mMessageArea.h = h;
    mTextField.setSize(w, h);
}

void Script::setVisible(bool visible) {
    mVisible = visible;
}

// Handle input events
void Script::handleEvent(const SDL_Event& e)
{
    if (mVisible) {
        mTextField.handleEvent(const_cast<SDL_Event*>(&e)); // Handle text input

        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
        {
            sendMessage(); // Send the message
        }
    }
}

// Render the script window
void Script::render()
{
    if (mVisible) {
        // Render older messages
        renderMessages();

        // Render the input text field
        mTextField.render();
    }
}

// Toggle visibility of the script
void Script::toggleVisibilityChat()
{
    mVisible = !mVisible;
}

// Check if the script is visible
bool Script::isVisible() const
{
    return mVisible;
}

void Script::join(Acteur* a)
{
}

void Script::add_inspector(Inspector* inspector_p)
{
    inspector = inspector_p;
}

Inspector* Script::get_inspector()
{
    return inspector;
}

std::string Script::pop_message()
{
    std::string m;
    if (!mMessages.empty()) {
        m = mMessages.back();
        std::cout << "Popping: " << m << std::endl;
        mMessages.pop_back();
    }
    return m;
}

bool Script::message_alert()
{
    if (mMessages.size() != 0) return true;
}

// Send the current message
void Script::sendMessage()
{
    if (!mTextField.getText().empty()) {
        std::cout << "Message sent." << std::endl;
        std::string message = mTextField.getText();
        std::cout << message << std::endl;

        mMessages.push_back(message); // Store the message
        mTextField.setText(""); // Clear the text field
    }
    else
    {
        std::cout << "Message too short." << std::endl;
    }
}

// Render stored messages
void Script::renderMessages()
{
    int messageY = mMessageArea.y + mMessageArea.h; // Start rendering from the bottom

    for (auto it = mMessages.rbegin(); it != mMessages.rend(); ++it) // Iterate in reverse order to render newest at the bottom
    {
        SDL_Surface* messageSurface = TTF_RenderText_Solid(mTextField.getFont(), it->c_str(), { 0, 0, 0, 255 });

        if (messageSurface != nullptr) {
            SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(mTextField.getRenderer(), messageSurface);
            if (messageTexture != nullptr) {
                SDL_Rect messageRect = { mMessageArea.x, messageY - messageSurface->h, messageSurface->w, messageSurface->h };
                SDL_RenderCopy(mTextField.getRenderer(), messageTexture, nullptr, &messageRect);
                SDL_DestroyTexture(messageTexture);

                messageY -= messageSurface->h + 5; // Move up for the next message, with some padding
            }

            SDL_FreeSurface(messageSurface);
        }
    }
}

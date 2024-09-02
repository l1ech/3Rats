#include "Text.h"

#include <vector>
#include <sstream>
Text::Text()
{
}

Text::~Text()
{
	// Don't forget to free your surface and texture
	SDL_FreeSurface(surface_message);
	SDL_DestroyTexture(Message);
}

// Helper function to split a string by a delimiter
std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void Text::update(std::string text) {
    // Split text into lines
    std::vector<std::string> lines = split(text, '\n');

    // Free previous resources
    if (surface_message) {
        SDL_FreeSurface(surface_message);
    }
    if (Message) {
        SDL_DestroyTexture(Message);
    }

    // Create a new surface for each line and render each line as a separate texture
    for (const auto& line : lines) {
        surface_message = TTF_RenderText_Solid(font, line.c_str(), colour);
        if (!surface_message) {
            std::cerr << "Error creating surface: " << SDL_GetError() << std::endl;
            return;
        }

        Message = SDL_CreateTextureFromSurface(render_target, surface_message);
        if (!Message) {
            std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
            return;
        }

        // Adjust the rectangle for the next line (you may need to adjust the line height)
        //message_rect.y += font_size;  // Assuming font_size as the line height
    }
}

void Text::draw(SDL_Renderer* renderTarget) {
    // Render each line of text at the appropriate coordinates
    int originalY = message_rect.y;
    std::vector<std::string> lines = split(display_text, '\n'); // Assuming you store the text in current_text

    for (const auto& line : lines) {
        // Render the texture for this line
        surface_message = TTF_RenderText_Solid(font, line.c_str(), colour);
        Message = SDL_CreateTextureFromSurface(render_target, surface_message);

        SDL_RenderCopy(renderTarget, Message, NULL, &message_rect);

        // Move the rectangle down for the next line
        message_rect.y += font_size; // Assuming font_size as the line height
    }

    // Reset the y coordinate after rendering all lines
    message_rect.y = originalY;
}


void Text::set_renderer(SDL_Renderer* renderTarget)
{
	render_target = renderTarget;
}

void Text::init(std::string font_path, int font_size, SDL_Color colour, int x, int y, int w, int h)
{
	this->font_path = font_path;
	this->font_size = font_size;
	this->colour = colour;

	font = TTF_OpenFont("fonts/sans.ttf", font_size);
	if (font == NULL)
	{
		std::cout << "Error Font" << std::endl;
	}

	surface_message = TTF_RenderText_Solid(font, "99:99", colour);
	Message = SDL_CreateTextureFromSurface(render_target, surface_message);

	message_rect.x = x;  //controls the rect's x coordinate 
	message_rect.y = y; // controls the rect's y coordinte
	message_rect.w = w; // controls the width of the rect
	message_rect.h = h; // controls the height of the rect

	// (0,0) is on the top left of the window/screen,
	// think a rect as the text's box,
	// that way it would be very simple to understand
}

void Text::set_coords(int x, int y)
{
	message_rect.x = x;  //controls the rect's x coordinate 
	message_rect.y = y; // controls the rect's y coordinte
}

void Text::set_width(int w)
{
	message_rect.w = w; // controls the width of the rect
}

void Text::set_display_text(std::string t)
{
    display_text = t;
}




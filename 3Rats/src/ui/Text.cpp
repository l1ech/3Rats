#include "Text.h"

Text::Text()
{
}

Text::~Text()
{
	// Don't forget to free your surface and texture
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void Text::update(std::string text)
{
	message_string = text;
	// as TTF_RenderText_Solid could only be used on
	// SDL_Surface then you have to create the surface first
	surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), colour);


	// now you can convert it into a texture
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

}

void Text::draw(SDL_Renderer* renderTarget)
{
	std::cout << "[Text]: Drawing at x: " << Message_rect.x 
				<< ", y: " << Message_rect.y 
				<< ", width: " << Message_rect.w 
				<< ", height: " << Message_rect.h 
				<< ", message: " << message_string
				<< std::endl;

	if (Message && renderer) {
		if (SDL_RenderCopy(renderer, Message, NULL, &Message_rect) != 0) {
			std::cerr << "[Text]: Error rendering texture: " << SDL_GetError() << std::endl;
		}
	} else {
		std::cerr << "[Text]: Cannot draw. Renderer or Message is null." << std::endl;
	}
	//std::cout << "draw!!!!!!" << std::endl;

	// Now since it's a texture, you have to put RenderCopy
	// in your game loop area, the area where the whole code executes

	// you put the renderer's name first, the Message,
	// the crop size (you can ignore this if you don't want
	// to dabble with cropping), and the rect which is the size
	// and coordinate of your texture
	SDL_RenderCopy(renderTarget, Message, NULL, &Message_rect);

}

void Text::set_renderer(SDL_Renderer* renderTarget)
{
	renderer = renderTarget;
}

void Text::init_text(std::string font_path, int font_size, SDL_Color colour, int x, int y, int w, int h)
{
	//Texture_Manager texture_manager;
	this->font_path = font_path;
	this->font_size = font_size;
	this->colour = colour;

	font = TTF_OpenFont(Texture_Constants::FONT.c_str(), 24);
	
	if (font == NULL)
	{
		std::cout << "[Text]Error Font" << std::endl;
	}

	surfaceMessage = TTF_RenderText_Solid(font, "99:99", colour);
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	Message_rect.x = x;  //controls the rect's x coordinate 
	Message_rect.y = y; // controls the rect's y coordinte
	Message_rect.w = w; // controls the width of the rect
	Message_rect.h = h; // controls the height of the rect

	// (0,0) is on the top left of the window/screen,
	// think a rect as the text's box,
	// that way it would be very simple to understand
}

void Text::set_coords(int x, int y)
{
	Message_rect.x = x;  //controls the rect's x coordinate 
	Message_rect.y = y; // controls the rect's y coordinte
}

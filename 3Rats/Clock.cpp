#include "Clock.h"

// the code from here is modified frome this stack echange
// https://stackoverflow.com/a/22889483/18288994


Clock::Clock()
{
	update_time = true;
}

Clock::~Clock()
{
	// Don't forget to free your surface and texture
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}


void Clock::set_renderer(SDL_Renderer* renderTarget)
{
	renderer = renderTarget;

}

void Clock::load()
{
	

	//this opens a font style and sets a size
	font = TTF_OpenFont("fonts/sans.ttf", 24);
	if (font == NULL)
	{
		std::cout << "Error Font" << std::endl;
	}
		
	// this is the color in rgb format,
	// maxing out all would give you the color white,
	// and it will be your text's color
	red = { 255, 0, 0 };

	// as TTF_RenderText_Solid could only be used on
	// SDL_Surface then you have to create the surface first
	surfaceMessage = TTF_RenderText_Solid(font, "99:99", red);

	// now you can convert it into a texture
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	Message_rect.x = 400;  //controls the rect's x coordinate 
	Message_rect.y = 330; // controls the rect's y coordinte
	Message_rect.w = 200; // controls the width of the rect
	Message_rect.h = 90; // controls the height of the rect

	// (0,0) is on the top left of the window/screen,
	// think a rect as the text's box,
	// that way it would be very simple to understand

	

	
}

void Clock::update(double delta)
{
	count += delta;

	//std::cout << count << std::endl;

	if (count >= 5)
	{
		count = 0;
		min++;
		update_time = true;
	}

	if (min >= 60)
	{
		min = 0;
		hour++;
		update_time = true;
	}

	if (hour >= 24)
	{
		hour = 0;
		update_time = true;
	}

	str_time_min = std::to_string((int)min);
	str_time_hour = std::to_string((int)hour);

	if (str_time_min.size() == 1)
	{
		str_time_min = "0" + str_time_min;
	}

	if (str_time_hour.size() == 1)
	{
		str_time_hour = "0" + str_time_hour;
	}

	time = str_time_hour + ":" + str_time_min;

	// befor i made it with this update flag memory was to big to fast. 
	// alternative idea: somehow free space like in the ~clock.

	if (update_time)
	{
		// as TTF_RenderText_Solid could only be used on
		// SDL_Surface then you have to create the surface first
		surfaceMessage = TTF_RenderText_Solid(font, time.c_str(), red);


		// now you can convert it into a texture
		Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		update_time = false;
	}
}

void Clock::draw(SDL_Renderer* renderTarget)
{
	(*clockframe).draw(renderTarget);

	//std::cout << "draw!!!!!!" << std::endl;

	// Now since it's a texture, you have to put RenderCopy
	// in your game loop area, the area where the whole code executes

	// you put the renderer's name first, the Message,
	// the crop size (you can ignore this if you don't want
	// to dabble with cropping), and the rect which is the size
	// and coordinate of your texture
	SDL_RenderCopy(renderTarget, Message, NULL, &Message_rect);

	
}

void Clock::set_up(Body* clock_frame_ptr)
{
	this->clockframe = clock_frame_ptr;
}

void Clock::set_time(int hour, int min)
{
	count = 0;
	this->min = min;
	this->hour = hour;
}

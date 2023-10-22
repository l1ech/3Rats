#include "Body.h"
#include <memory>

Body::Body() { }

Body::~Body() { SDL_DestroyTexture(texture); }

void Body::update(float delta) { }

void Body::draw(SDL_Renderer* renderTarget) { SDL_RenderCopy(renderTarget, texture, &crop_rect, &position_rect); }

void Body::set_renderer(SDL_Renderer* renderTarget)
{
	texture_path = "meta_textures/place_holder.png";
	render_target = renderTarget;

	SDL_Surface* surface = IMG_Load(texture_path.c_str());
	if (surface == NULL)
		std::cout << "Error Body Surface" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(render_target, surface);
		if (texture == NULL)
			std::cout << "Error Body Texture" << std::endl;
	}

	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, NULL, NULL, &crop_rect.w, &crop_rect.h);
}

void Body::init(std::string path, int x, int y, int h, int framesX, int framesY)
{
}

void Body::set_texture(std::string path)
{
	texture_path = path;

	SDL_Surface* surface = IMG_Load(texture_path.c_str());
	if (surface == NULL)
		std::cout << "Error Body Surface" << std::endl;
	else
	{
		texture = SDL_CreateTextureFromSurface(render_target, surface);
		if (texture == NULL)
			std::cout << "Error Body Texture" << std::endl;
	}

	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, NULL, NULL, &crop_rect.w, &crop_rect.h);

}

void Body::set_cords(int x, int y)
{
	position_rect.x = x;
	position_rect.y = y;

	texture_width = crop_rect.w;

	frame_width = position_rect.w = crop_rect.w;
	frame_height = position_rect.h = crop_rect.h;

	origin_x = frame_width / 2;
	origin_y = frame_height / 2;

	radius = frame_width / 2;
}

void Body::set_hight(int h) { this->hight = h; }

void Body::set_cords_frames(int x, int y, int framesX, int framesY)
{

	position_rect.x = x;
	position_rect.y = y;

	texture_width = crop_rect.w;

	crop_rect.w /= framesX;
	crop_rect.h /= framesY;

	frame_width = position_rect.w = crop_rect.w;
	frame_height = position_rect.h = crop_rect.h;

	origin_x = frame_width / 2;
	origin_y = frame_height / 2;

	radius = frame_width / 2;
}


int Body::get_hight() { return this->hight; }

int Body::get_origin_x() { return position_rect.x + origin_x; }

int Body::get_origin_y() { return position_rect.y + origin_y; }

int Body::get_radius() { return radius; }
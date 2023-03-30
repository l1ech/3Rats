#pragma once	

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>

class Body
{
protected:
	SDL_Renderer* ptr_renderer;
	SDL_Texture* texture;

	std::string filePath;

	SDL_Rect positionRect;
	SDL_Rect cropRect;

	float frameWidth, frameHeight;
	int textureWidth;

	int originX, originY;
	int radius;

	int hight;

public:

	Body();
	~Body();

	void update(float delta);
	void draw(SDL_Renderer* renderTarget);

	void set_surface(SDL_Renderer* renderTarget);
	void set_texture(std::string name);
	void set_cords(int x, int y);
	void set_hight(int value);

	int get_origin_x();
	int get_origin_y();
	int get_radius();
	int get_hight();
};
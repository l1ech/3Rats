#pragma once	

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>

class Body
{
protected:
	SDL_Rect cropRect;
	SDL_Texture* texture;
	SDL_Rect positionRect;

	SDL_Renderer* ptr_renderer;

	float frameCounter, searchCounter;
	float frameWidth, frameHeight;
	int textureWidth;
	SDL_Scancode keys[4];
	int originX, originY;
	int radius;
	std::string filePath;

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
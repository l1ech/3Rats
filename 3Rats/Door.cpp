#include "Door.h"

Door::Door(int x_pos, int y_pos, int t)
{
	x = x_pos;
	y = y_pos;
	type = t;
}

Door::Door()
{
	x = 0;
	y = 0;
	type = 0;
}

int Door::get_x()
{
	return x;
}

int Door::get_y()
{
	return y;
}

int Door::get_type()
{
	return type;
}

void Door::init_door(int x_pos, int y_pos, int t)
{
	x = x_pos;
	y = y_pos;
	type = t;
}

void Door::set_cords(int x_pos, int y_pos)
{
	x = x_pos;
	y = y_pos;
}

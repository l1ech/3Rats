#include "Info.h"

std::string Info::sliceMessage(const std::string& str, size_t n) {
	// Ensure n does not exceed the string length
	if (n > str.length()) {
		n = str.length();
	}
	return str.substr(0, n);
}


void Info::update(std::string update_text, double delta)
{

	if(on_screen)time += delta;
	if (time >= 0.1)
	{
		character++;
		time = 0;
		if (character <= 122) {
			set_width(character * 5);
		}
		else if (character >= 140) {
			//set_fadeout(character - 122);
			out();
		}
		
	}
	this->display_text = sliceMessage(update_text, character);
	Panel::update();
}

bool Info::is_on_screen()
{
	return on_screen;
}

void Info::toggle()
{
	if (on_screen)
	{
		out();
	}
	else
	{
		in();
	}
}
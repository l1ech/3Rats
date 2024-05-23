#pragma once

#include "Panel.h"
#include "Button.h"

class Info : public Panel
{
private:
	double time = 0;
	int character;

	std::string sliceMessage(const std::string& str, size_t n);

public:
	void update(std::string update_text, double delta);

	bool is_on_screen();
	void toggle();

};
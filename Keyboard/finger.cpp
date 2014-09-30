#include "finger.h"
#include <map>

finger::finger()
{
	finger("", 0);
}

finger::finger(char* str, int* positions)
{
	movement = 0;
	position = 2;
	buttons = map<char, int>();
	count_pressed = map<char, int>();	
	int i = 0;
	while (char c = str[i] != '\0') {
		buttons[c] = positions[i++];
		count_pressed[c] = 0;
	}
}

finger::finger(const finger& f)
{
	this->movement = f.movement;
	this->buttons = f.buttons;
	this->position = f.position;
	this->count_pressed = f.count_pressed;
}

finger& finger::operator=(const finger& f)
{
	this->movement = f.movement;
	this->buttons = f.buttons;
	this->position = f.position;
	this->count_pressed = f.count_pressed;
}

void finger::press(char c)
{
	count_pressed[c]++;
	if (position != buttons[c]) {
		movement++;
		position = buttons[c];
	}
}

finger::~finger()
{
}

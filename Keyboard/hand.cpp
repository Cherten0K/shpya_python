#include "hand.h"
using namespace std;

hand::hand(finger &thumb, finger &forefinger, finger &middle_finger, finger &ring_finger, finger &pinky)
{	
	this->thumb = thumb;
	this->forefinger = forefinger;
	this->middle_finger = middle_finger;
	this->ring_finger = ring_finger;
	this->pinky = pinky;
}

bool hand::press(char c)
{
	if (thumb.buttons.at(c)){
		thumb.press(c);
		return true;
	}
	if (forefinger.buttons.at(c)){
		forefinger.press(c);
		return true;
	}
	if (middle_finger.buttons.at(c)){
		middle_finger.press(c);
		return true;
	}
	if (ring_finger.buttons.at(c)){
		ring_finger.press(c);
		return true;
	}
	if (pinky.buttons.at(c)){
		pinky.press(c);
		return true;
	}
	return false;
}

hand::~hand()
{
}

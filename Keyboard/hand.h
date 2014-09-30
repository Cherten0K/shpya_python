#pragma once
#include "finger.h"
class hand
{
public:
	map < char, int > fingers;	
	finger thumb;
	finger forefinger;
	finger middle_finger;
	finger ring_finger;
	finger pinky;
	hand(finger &thumb, finger &forefinger, finger &middle_finger, finger &ring_finger, finger &pinky);
	bool press(char);
	~hand();
};


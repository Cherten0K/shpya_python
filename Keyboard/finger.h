#pragma once
#include <collection.h>
#include <algorithm>
using namespace std;

class finger
{
public:
	int position;
	int movement;
	map<char, int> buttons;
	map<char, int> count_pressed;
	finger();
	finger(char*, int*);
	finger(const finger&);
	finger& operator=(const finger&);
	void press(char);
	~finger();
};


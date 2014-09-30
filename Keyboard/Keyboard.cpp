#include <iostream>
#include <fstream>
#include "finger.h"
#include "hand.h"

int main()
{
	hand right_hand = hand(finger(" ", new int[]{ 0 }), 
							   finger("òüîğíã7?", new int[]{1, 1, 2, 2, 3, 3, 4, 4}), 
							   finger("áëø89*(", new int[]{1, 2, 4, 4, 4, 4}),
							   finger("şäù0)", new int[]{1, 2, 3, 4, 4}),
							   finger(".,æıõú-=+\n", new int[]{1, 1, 2, 2, 3, 3, 4, 4}));
	hand left_hand = hand(finger(" ", new int[]{ 0 }),
		finger("ñìèàïêå56%:", new int[]{1, 1, 2, 2, 3, 3, 4, 4, 4, 4}),
		finger("÷âó34¹;", new int[]{1, 2, 3, 4, 4, 4, 4}),
		finger("ÿûö12!\"", new int[]{1,2,3,4,4,4,4}),
		finger("ôé\t", new int[]{1, 1, 2, 2, 3, 3, 4, 4}));
	ifstream in;
	in.open("input.txt");
	char c;
	while (in >> c)
	{
		if (!right_hand.press(c)) left_hand.press(c);
	}
	return 0;
}
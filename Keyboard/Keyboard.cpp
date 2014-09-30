#include <iostream>
#include <fstream>
#include "finger.h"
#include "hand.h"

int main()
{
	hand right_hand = hand(finger(" ", new int[]{ 0 }), 
							   finger("������7?", new int[]{1, 1, 2, 2, 3, 3, 4, 4}), 
							   finger("���89*(", new int[]{1, 2, 4, 4, 4, 4}),
							   finger("���0)", new int[]{1, 2, 3, 4, 4}),
							   finger(".,����-=+\n", new int[]{1, 1, 2, 2, 3, 3, 4, 4}));
	hand left_hand = hand(finger(" ", new int[]{ 0 }),
		finger("�������56%:", new int[]{1, 1, 2, 2, 3, 3, 4, 4, 4, 4}),
		finger("���34�;", new int[]{1, 2, 3, 4, 4, 4, 4}),
		finger("���12!\"", new int[]{1,2,3,4,4,4,4}),
		finger("��\t", new int[]{1, 1, 2, 2, 3, 3, 4, 4}));
	ifstream in;
	in.open("input.txt");
	char c;
	while (in >> c)
	{
		if (!right_hand.press(c)) left_hand.press(c);
	}
	return 0;
}
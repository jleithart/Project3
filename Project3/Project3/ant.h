#pragma once
#include "globals.h"
#include <stack>
#include <iostream>

#define LEFT 0
#define UP	1
#define RIGHT 2
#define DOWN 3


class ant
{
public:
	ant(void);
	~ant(void);
	void TurnLeft();
	void TurnRight();
	void MoveForward();

	void Evaluate();
	int GetFood() { return foodCollected; }

private:
	int direction;
	int x_pos;
	int y_pos;
	int foodCollected;
	//node *root;
};


#ifndef _ANT_H
#define _ANT_H

#include "globals.h"
#include "node.h"
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
	void InitBoard();
	void PrintBoard();
	void UpdateFace();
	void mutate();

	node *CopyAnt();

	void SetRoot(node * n) {root = n;}
	node *GetRoot()	{return this->root;}

	bool CheckFoodAhead();
	int GetSize() { return root->GetSize(); }

	node *root;

private:
	char curBoard[32][32];
	char bug;
	int direction;
	int x_pos;
	int y_pos;
	int foodCollected;
};

#endif
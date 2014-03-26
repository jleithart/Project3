#include "ant.h"


ant::ant(void)
{
	this->direction = RIGHT;
	this->x_pos = 0;
	this->y_pos = 0;
	board[0][0] = 0;
}


ant::~ant(void)
{
}

void ant::TurnLeft(){
	this->direction = (this->direction + 1) % 4;
}

void ant::TurnRight(){
	this->direction = (this->direction - 1) % 4;
}

void ant::MoveForward(){
	switch(this->direction){
	case LEFT:
		x_pos = (x_pos - 1) % 32;
		break;
	case RIGHT:
		x_pos = (x_pos + 1) % 32;
		break;
	case UP:
		y_pos = (y_pos - 1) % 32;
		break;
	case DOWN:
		y_pos = (y_pos + 1) % 32;
		break;
	}
	if(board[this->y_pos][this->x_pos] == 1){
		this->foodCollected++;
	}
	board[this->y_pos][this->x_pos] = 0;
}

void ant::Evaluate(){
	int numSteps = 600;
	//node *n = this->root;
	std::stack <int> nodestack;
	while(numSteps > 0){
		n = this->root;
		while(!nodestack.empty()){
			switch(n->type){
				case prog3:
					nodestack.push(n->right);
					nodestack.push(n->mid);
					nodestack.push(n->left);
					break;
				case prog2:
					nodestack.push(n->right);
					nodestack.push(n->left);
					break;
				case iffood:
					nodestack.push(n->right);
					nodestack.push(n->left);
					break;
				case left:
					this->TurnLeft();
					numSteps--;
					break;
				case right:
					this->TurnRight();
					numSteps--;
					break;
				case forward:
					this->MoveForward();
					numSteps--;
					break;
			}
			n = nodestack.top();
			nodestack.pop();
		}

	}
}
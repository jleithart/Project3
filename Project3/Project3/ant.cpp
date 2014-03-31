#include "ant.h"


ant::ant(void)
{
	this->direction = RIGHT;
	this->x_pos = 0;
	this->y_pos = 0;
	bug = '>';
	InitBoard();
	foodCollected = 1;
	curBoard[0][0] = bug;
	this->root = new node();
	this->root->type = prog3;
	this->root->generate(5, NULL);

}


ant::~ant(void)
{
}

void ant::TurnLeft(){
	this->direction = ((this->direction+4) + 1) % 4;
	UpdateFace();
}

void ant::TurnRight(){
	this->direction = ((this->direction+4) - 1) % 4;
	UpdateFace();
}

void ant::UpdateFace(){
	switch(this->direction){
	case LEFT:
		this->bug = '>';
		break;
	case RIGHT:
		this->bug = '<';
		break;
	case UP:
		this->bug = '^';
		break;
	case DOWN:
		this->bug = 'v';
		break;
	}
}

void ant::MoveForward(){
	switch(this->direction){
	case LEFT:
		x_pos = ((x_pos+32) - 1) % 32;
		break;
	case RIGHT:
		x_pos = ((x_pos+32) + 1) % 32;
		break;
	case UP:
		y_pos = ((x_pos+32) - 1) % 32;
		break;
	case DOWN:
		y_pos = ((x_pos+32) + 1) % 32;
		break;
	}
	if(curBoard[this->y_pos][this->x_pos] == 1){
		this->foodCollected++;
	}
	curBoard[y_pos][x_pos] = this->bug;
}

void ant::Evaluate(){
	int numSteps = 600;
	node *n = this->root;
	std::stack <node *> nodestack;
	while(numSteps > 0){
		n = this->root;
		nodestack.push(n);
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
				case type_left:
					this->TurnLeft();
					numSteps--;
					break;
				case type_right:
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

void ant::PrintBoard(){
	for(int y = 0; y < 32; y++){
		for(int x = 0; x < 32; x++){
			std::cout << curBoard[y][x];
		}
		std::cout << std::endl;
	}
}

void ant::InitBoard(){
	for(int y = 0; y < 32; y++){
		for(int x = 0; x < 32; x++){
			curBoard[y][x] = (char) board[y][x];
		}
	}
}
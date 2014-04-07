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
	this->root->generate(4, NULL);

}


ant::~ant(void)
{
}

node * ant::CopyAnt(){
	node *n = new node();
	n = this->root->copyTree(root, NULL);
	return n;
}

void ant::mutate(){
	this->root->mutate();
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
		this->bug = '<';
		break;
	case RIGHT:
		this->bug = '>';
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
	curBoard[y_pos][x_pos] = this->bug;
	switch(this->direction){
	case LEFT:
		x_pos = ((x_pos+32) - 1) % 32;
		break;
	case RIGHT:
		x_pos = ((x_pos+32) + 1) % 32;
		break;
	case UP:
		y_pos = ((y_pos+32) - 1) % 32;
		break;
	case DOWN:
		y_pos = ((y_pos+32) + 1) % 32;
		break;
	}
	if(curBoard[this->y_pos][this->x_pos] == 1){
		this->foodCollected++;
	}
}

bool ant::CheckFoodAhead(){
	switch(this->direction){
	case LEFT:
		if(curBoard[y_pos][((x_pos+32) - 1) % 32] == 1){
			return true;
		}
		break;
	case RIGHT:
		if(curBoard[y_pos][((x_pos+32) + 1) % 32] == 1){
			return true;
		}
		break;
	case UP:
		if(curBoard[((y_pos+32) - 1) % 32][x_pos] == 1){
			return true;
		}
		break;
	case DOWN:
		if(curBoard[((y_pos+32) + 1) % 32][x_pos] == 1){
			return true;
		}
		break;
	}
	return false;
}

void ant::Evaluate(){
	int numSteps = 600;
	this->direction = RIGHT;
	this->x_pos = 0;
	this->y_pos = 0;
	bug = '>';
	InitBoard();
	foodCollected = 1;
	curBoard[0][0] = bug;

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
					if(CheckFoodAhead()){
						nodestack.push(n->left);
					}
					else{
						nodestack.push(n->right);
					}
					
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
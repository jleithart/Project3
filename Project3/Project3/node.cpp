#include "node.h"


node::node(void)
{
	this->left = NULL;
	this->mid = NULL;
	this->right = NULL;
	this->parent = NULL;
	this->type = static_cast <OPTYPE> (rand()%last);
}


node::~node(void)
{
	if(this != NULL){
		this->left->~node();
		this->mid->~node();
		this->right->~node();
	}
	delete this;
}

void node::generate(int depth, node* p){
	this->parent = p;
	if(depth != 0){
		switch(this->type){
			case prog3:
				this->left = new node();
				this->left->generate(depth - 1, this);
				this->mid = new node();
				this->mid->generate(depth - 1, this);
				this->right = new node();
				this->right->generate(depth - 1, this);
				break;
			case prog2:
				this->left = new node();
				this->left->generate(depth-1, this);
				this->right = new node();
				this->right->generate(depth-1, this);
				break;
			case iffood:
				this->left = new node();
				this->left->generate(depth-1, this);
				this->right = new node();
				this->right->generate(depth-1, this);
				break;
			default:
				//std::cout << "ERROR: subtype out of range" << std::endl;
				break;
		}
	}
	else{
		this->type = static_cast <OPTYPE> (rand()%prog3);
	}
}

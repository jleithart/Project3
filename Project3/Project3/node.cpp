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
		if(this->left != NULL){
			this->left->~node();
			this->left = NULL;
			delete this->left;
		}
		if(this->mid != NULL){
			this->mid->~node();
			this->mid = NULL;
			delete this->mid;
		}
		if(this->right != NULL){
			this->right->~node();
			this->right = NULL;
			delete this->right;
		}
	}
	//this = NULL;
}

node * node::copyTree(node *old, node *p){
	if(old == NULL){
		return NULL;
	}
	node *n = new node();
	n->parent = p;
	n->type = old->type;
	n->left = n->copyTree(old->left, n);
	n->mid = n->copyTree(old->mid, n);
	n->right = n->copyTree(old->right, n);
	return n;
}

void node::mutate(){
	int mutateChance = rand()%100;
	int typeChance = 0;
	if(mutateChance < 5){
		switch(this->type){
			case type_left:
			case type_right:
			case forward:
				this->type = static_cast <OPTYPE> (rand()%prog3);
				break;
			case prog3:
				typeChance = rand()%2;
				if(typeChance == 0){
					type = prog2;
				}
				else{
					type = iffood;
				}
				this->mid->~node();
				break;
			case prog2:
				typeChance = rand()%2;
				if(typeChance == 0){
					type = prog3;
					this->mid = new node();
					this->mid->generate(0, this);
				}
				else{
					type = iffood;
				}
			case iffood:
				typeChance = rand()%2;
				if(typeChance == 0){
					type = prog2;
				}
				else{
					type = prog3;
					this->mid = new node();
					this->mid->generate(0, this);
				}
				break;
		}
	}
	//traverse
	if(this->left != NULL){
		this->left->mutate();
	}
	if(this->mid != NULL){
		this->mid->mutate();
	}
	if(this->right != NULL){
		this->right->mutate();
	}
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

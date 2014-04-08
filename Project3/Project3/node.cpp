#include "node.h"


node::node(void)
{
	this->left = NULL;
	this->mid = NULL;
	this->right = NULL;
	this->parent = NULL;
	this->loc = root;
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

int node::GetSize(){
	if(this == NULL){
		return 0;
	}
	int total = 1;
	if(this->left != NULL){
		total += this->left->GetSize();
	}
	if(this->mid != NULL){
		total += this->mid->GetSize();
	}
	if(this->right != NULL){
		total += this->right->GetSize();
	}
	return total;
}

node * node::copyTree(node *old, node *p){
	if(old == NULL){
		return NULL;
	}
	node *n = new node();
	n->parent = p;
	n->type = old->type;
	n->loc = old->loc;
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
					this->mid->generate(0, this, nmid);
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
					this->mid->generate(0, this, nmid);
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

void node::generate(int depth, node* p, NODELOC l){
	this->parent = p;
	this->loc = l;
	if(depth != 0){
		switch(this->type){
			case prog3:
				this->left = new node();
				this->left->generate(depth - 1, this, nleft);
				this->mid = new node();
				this->mid->generate(depth - 1, this, nmid);
				this->right = new node();
				this->right->generate(depth - 1, this, nright);
				break;
			case prog2:
				this->left = new node();
				this->left->generate(depth-1, this, nleft);
				this->right = new node();
				this->right->generate(depth-1, this, nright);
				break;
			case iffood:
				this->left = new node();
				this->left->generate(depth-1, this, nleft);
				this->right = new node();
				this->right->generate(depth-1, this, nright);
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

void node::PrintTree(node *n){
	while(n != NULL){
		switch(n->type){
			case prog3:
				std::cout << "Prog 3" << std::endl;
				std::cout << "|\tLeft"<< std::endl;
				PrintTree(n->left);
				std::cout << "|\tMid"<< std::endl;
				PrintTree(n->mid);
				std::cout << "|\tRight"<< std::endl;
				PrintTree(n->right);
				break;
			case prog2:
				std::cout << "Prog 2" << std::endl;
				std::cout << "|\tLeft"<< std::endl;
				PrintTree(n->left);
				std::cout << "|\tRight"<< std::endl;
				PrintTree(n->right);
				break;
			case iffood:
				std::cout << "If Food Ahead" << std::endl;
				std::cout << "|\tLeft"<< std::endl;
				PrintTree(n->left);
				std::cout << "|\tRight"<< std::endl;
				PrintTree(n->right);
				break;
			case type_left:
				std::cout << "Turn Left" << std::endl;
				n = n->left;
				break;
			case type_right:
				std::cout << "Turn Right" << std::endl;
				n = n->left;
				break;
			case forward:
				std::cout << "Move Forward" << std::endl;
				n = n->left;
				break;
		}
	}
}

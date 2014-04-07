#ifndef NODE_H
#define NODE_H
#include <iostream>

enum OPTYPE {type_left, type_right, forward, prog3, prog2, iffood, last};

class node
{
public:
	OPTYPE type;
	node *left;
	node *mid;
	node *right;

	node *parent;

	node(void);
	~node(void);
	void generate(int, node*);
	void mutate();
	void copyTree();
};

#endif
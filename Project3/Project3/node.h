#ifndef NODE_H
#define NODE_H
#include <iostream>

enum OPTYPE {type_left, type_right, forward, prog3, prog2, iffood, last};

enum NODELOC {root, nleft, nmid, nright};

class node
{
private:
public:
	NODELOC loc;
	OPTYPE type;
	node *left;
	node *mid;
	node *right;

	node *parent;

	node(void);
	~node(void);
	void generate(int, node*, NODELOC l = root);
	void mutate();
	node * copyTree(node *, node *);
	node * GetSubTree(int);

	int GetSize();

	void PrintTree(node *);

};

#endif
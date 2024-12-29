#ifndef BITREE_H
#define BITREE_H

#include "Node.h" 

class BiTree {
	Node *root; 
	void PrintCall(Node*); 
public: 
	BiTree(int); 
	void Insert(int); 
	void Print(); 
};

#endif

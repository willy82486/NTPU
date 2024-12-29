#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

class Node {
	int num;
	Node *left, *right;
public:
	Node(int, Node* = NULL, Node* = NULL);
	void SetNum(int);
	int GetNum();
	void SetLeft(Node*);
	Node* GetLeft();
	void SetRight(Node*);
	Node* GetRight();
};

#endif

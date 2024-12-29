#include "Node.h"

Node::Node(int n, Node *l, Node *r) { 
	SetNum(n); 
	SetLeft(l);
	SetRight(r); 
}

void Node::SetNum(int n) { 
	num = n; 
}

int Node::GetNum() {
	return num;
}

void Node::SetLeft(Node *l) { 
	left = l;
}

Node *Node::GetLeft() { 
	return left; 
}

void Node::SetRight(Node *r) { 
	right = r; 
}

Node *Node::GetRight() {
	return right; 
}

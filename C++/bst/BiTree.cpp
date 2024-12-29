#include "BiTree.h"
#include <iostream>
using namespace std;

BiTree::BiTree(int n) {
	root = new Node(n);
}

void BiTree::Insert(int n) {
	Node *tmp = root;

	while ( tmp->GetNum() != n ) {
		if ( tmp->GetNum() < n ) {
			if ( tmp->GetRight() != NULL ) {
				tmp = tmp->GetRight();
			}
			else {
				//tmp = new Node(n);
				tmp->SetRight(new Node(n));
				break;
			}
		}
		else {
			if ( tmp->GetLeft() != NULL ) {
				tmp = tmp->GetLeft();
			}
			else {
				//tmp = new Node(n);
				tmp->SetLeft(new Node(n));
				break;
			}
		}
	}
}


void BiTree::Print() {
	PrintCall(root);
	cout << endl;
}

void BiTree::PrintCall(Node *tmp) {
	if ( tmp->GetLeft() != NULL )
		PrintCall( tmp->GetLeft() );

	cout << tmp->GetNum() << " ";

	if ( tmp->GetRight() != NULL )
		PrintCall( tmp->GetRight() );
}

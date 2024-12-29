//#include "Node.h"
#include "BiTree.h"

int main() {

	int i;
	cin >> i;
	BiTree tree(i);

	cin >> i;
	tree.Insert(i);
	cin >> i;
	tree.Insert(i);

	tree.Print();

	return 0;
}

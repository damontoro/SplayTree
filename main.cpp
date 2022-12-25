#include <iostream>
#include "Splaytree.cpp"

using namespace std;

auto main(void) -> int {

	Splaytree<int> tree;
	tree.insert(5);
	tree.insert(3);
	tree.insert(7);
	auto it = tree.find(3);
	cout << it->value << endl;
	tree.remove(3);
	it = tree.find(3);
	if(it == nullptr) cout << "3 is not in the tree" << endl;
}
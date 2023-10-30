#include <iostream>
#include "../Trees/Node.h"
#include "../Trees/BaseBinaryTree.h"

using namespace rut::cip;
int main()
{
	Node<int> node{ 1 };
	Node<int> other{ 2 };
	std::cout << (node != other) << std::endl;

	BaseBinaryTree<int> tree{ 1, 2, 3 };
	std::cout << tree.InOrderPrint() << std::endl;
	return 0;
}
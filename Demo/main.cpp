#include <iostream>
#include "../Trees/Node.h"

using namespace rut::cip;
int main()
{
	Node<int> node{ 1 };
	Node<int> other{ 2 };
	std::cout << (node != other) << std::endl;
	return 0;
}
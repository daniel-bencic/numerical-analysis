#include <iostream>
#include "matrix.hh"

int main(int argc, char *argv[])
{
	num::Matrix<double> m{ 3, 2 };
	m(0, 1) = 2;
	std::cout << m << std::endl;
	m.transpose();
	std::cout << m << std::endl;
	return 0;
}

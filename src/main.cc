#include <iostream>
#include "matrix.hh"

int main(int argc, char *argv[])
{
	num::Matrix<double> m = num::create_identity_matrix<double>(3, 3);
	std::cout << m(0, 0) << std::endl;
	std::cout << m(0, 1) << std::endl;
	return 0;
}

#include <iostream>
#include <string>
#include <regex>
#include <cmath>
#include <limits>
#include "matrix.hh"
#include "linear-direct-solvers.hh"
#include "linear-iterative-solvers.hh"
#include "numerical-differentiation.hh"
#include "newton-raphson.hh"

bool read_matrix(num::linalg::Matrix<double>& mat, const std::string& msg);
int linear_algebra_mode(char algo);
int numerical_differentiation_mode(char algo);
int root_finding_mode(char algo);
void print_linear_system_solution(const num::linalg::LinearSolver<double>& solv);

int main(int argc, char *argv[])
{
	bool help = false, unkown = false;
	char c, mode, algorithm;
	while (--argc > 0 &&  (*++argv)[0] == '-') {
		while ((c = *++argv[0])) {
			switch (c) {
			case 'l':
			case 'd':
			case 'r':
			case 't':
				mode = c;
				break;
			case 'h':
				help = true;
	       			break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
				algorithm = c;
				break;
			default:
				std::cerr << "unrecognized command line option -" << c << "." << std::endl;
				argc = 0;
				unkown = true;
				break;
			}
		}
	}

	if (unkown) {
		std::cout <<  "Try: '-h'" << std::endl;
		return 0;
	}

	if (help) {
		std::cout << "USAGE: numerical-analysis [option]\n\n"
			  << "OPTIONS:\n"
			  << "        -l: linear algebra module\n"
			  << "                -1 gaussian elimination\n"
			  << "                -2 LU decomposition\n"
			  << "                -3 jacobi method\n"
			  << "                -4 gauss-seidel method\n"
			  << "                -5 successive over-relaxation\n"
			  << "        -d: numerical differentiation module\n"
			  << "                -1 first derivative\n"
			  << "                -2 second derivative\n"
			  << "        -r: root-finding module\n"
			  << "                -1 univariate\n"
			  << "                -2 multivariate\n"
			  << "        -t: TODO"
			  << std::endl;
		return 0;
	}

	if (mode == 'l') {
		return linear_algebra_mode(algorithm);
	} else if (mode == 'd') {
		return numerical_differentiation_mode(algorithm); 
	} else if (mode == 'r') {
		return root_finding_mode(algorithm);
	} else if (mode == 't') {
		std::cout << "TEST MODE (dev only)" << std::endl;
		num::linalg::Matrix<double> mat1;
		if (!read_matrix(mat1, "reading matrix (a00, a01[, ...];a10, a11[, ...][; ...]):")) {
			std::cout << "error reading matrix." << std::endl;
			return -1;
		}
	
		num::linalg::Matrix<double> mat2;
		if (!read_matrix(mat2, "reading matrix (a00, a01[, ...];a10, a11[, ...][; ...]):")) {
			std::cout << "error reading matrix." << std::endl;
			return -1;
		}
		
		std::cout << mat1 * mat2 << std::endl;
	}
	
	return 0;
}

bool read_matrix(num::linalg::Matrix<double>& mat, const std::string& msg)
{
	std::cout << msg << std::endl;
	std::string str;
	std::cin >> str;
	
	std::regex row_regex{ ".+?;" };
	std::regex col_regex{ "-?\\d+[.]?\\d*(?=,|;)" };

	std::sregex_iterator row_begin{ str.begin(), str.end(), row_regex };
	std::sregex_iterator row_end;
	for (std::sregex_iterator row_it = row_begin; row_it != row_end; ++row_it) {
		std::string row_str = row_it->str();

		std::vector<double> row;
		std::sregex_iterator col_begin{ row_str.begin(), row_str.end(), col_regex };
		for (std::sregex_iterator col_it = col_begin; col_it != row_end; ++col_it) {
			row.push_back(std::stod(col_it->str()));
		}

		mat.append_row(row);
	}
	
	return true;
}

int linear_algebra_mode(char algo)
{
	std::cout << "LINEAR ALGEBRA MODE" << std::endl;
		
	num::linalg::Matrix<double> mat;
	if (!read_matrix(mat, "reading matrix (a00, a01[, ...];a10, a11[, ...][; ...]):")) {
		std::cout << "error reading matrix." << std::endl;
		return -1;
	}
	
	num::linalg::Matrix<double> vec;
	if (!read_matrix(vec, "reading vector (a0; a1;[ ...;]:")) {
		std::cout << "error reading vector." << std::endl;
		return -1;
	}

	switch (algo) {
	case '1':
		print_linear_system_solution(num::linalg::GaussianElimination<double>(mat, vec));
		break;
	case '2':
		print_linear_system_solution(num::linalg::LUDecomposition<double>(mat, vec));
		break;
	case '3':
		print_linear_system_solution(num::linalg::JacobiMethod<double>(mat, vec, 1e-9, 100));
		break;
	case '4':
		print_linear_system_solution(num::linalg::GaussSeidelMethod<double>(mat, vec, 1e-9, 100));
		break;
	case '5':
		print_linear_system_solution(num::linalg::SOR<double>(mat, vec, 1e-9, 100, 1.1));
		break;
	}

	return 0;
}

int numerical_differentiation_mode(char algo)
{
	std::cout << "NUMERICAL DIFFERENTIATION MODE" << std::endl;

	num::linalg::Matrix<double> vec;
	if (!read_matrix(vec, "reading measurement vector (a0; a1;[ ...;]:")) {
		std::cout << "error reading vector." << std::endl;
		return -1;
	}

	double h = 0.0;
	std::cout << "reading measure distance h: " << std::endl;
	std::cin >> h;

	num::differ::NumDiffer<double> d = num::differ::NumDiffer<double>(vec, h, std::stoi(std::string(1, algo)));
	std::cout << "solution:\n" << std::setprecision(std::numeric_limits<double>::max_digits10) << d.derivated() << std::endl;

	return 0;
}

int root_finding_mode(char algo)
{
	std::cout << "ROOT-FINDING MODE" << std::endl;

	num::root::NewtonRaphson<double> nr = num::root::NewtonRaphson<double>(
		[] (double x) -> double { return x * x * x - 2; },
		[] (double x) -> double { return 3 * x * x; },
		2.0,
		1e-9,
		6
		);

	std::cout << "solution:\n" << std::setprecision(std::numeric_limits<double>::max_digits10) << nr.zero() << std::endl;
	
	return 0;
}

void print_linear_system_solution(const num::linalg::LinearSolver<double>& solv)
{
	std::cout << "solution:\n" << std::setprecision(std::numeric_limits<double>::digits10) << solv.x() << std::endl;
}

#include <iostream>
#include <string>
#include <regex>
#include "matrix.hh"
#include "direct-solvers.hh"

bool read_matrix(num::Matrix<double>& mat, const std::string& msg);
int linear_algebra_mode(char algo);
void print_linear_system_solution(const num::LinearSolver<double>& solv);

int main(int argc, char *argv[])
{
	bool help = false, unkown = false;
	char c, mode, algorithm;
	while (--argc > 0 &&  (*++argv)[0] == '-') {
		while (c = *++argv[0]) {
			switch (c) {
			case 'l':
			case 't':
				mode = c;
				break;
			case 'h':
				help = true;
	       			break;
			case '1':
			case '2':
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
			  << "        -t: TODO"
			  << std::endl;

		return 0;
	}

	if (mode == 'l') {
		return linear_algebra_mode(algorithm);
	} else if (mode == 't') {
		std::cout << "TEST MODE (dev only)" << std::endl;
		num::GaussianElimination<double> ge;
		num::Matrix<double> res = ge.solution();
		std::cout << res.cols() << std::endl;
	}
	
	return 0;
}

bool read_matrix(num::Matrix<double>& mat, const std::string& msg)
{
	std::cout << msg << std::endl;
	std::string str;
	std::cin >> str;
	
	std::regex row_regex{ ".+?;" };
	std::regex col_regex{ "[\\d.]+(?=,|;)" };

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
		
	num::Matrix<double> mat;
	if (!read_matrix(mat, "reading matrix (a00, a01[, ...];a10, a11[, ...][; ...]):")) {
		std::cout << "error reading matrix." << std::endl;
		return -1;
	}
	
	num::Matrix<double> vec;
	if (!read_matrix(vec, "reading vector (a0; a1;[ ...;]:")) {
		std::cout << "error reading vector." << std::endl;
		return -1;
	}

	switch (algo) {
	case '1':
		print_linear_system_solution(num::GaussianElimination<double>(mat, vec));
		break;
	case '2':
		print_linear_system_solution(num::LUDecomposition<double>(mat, vec));
		break;
	}

	return 0;
}

void print_linear_system_solution(const num::LinearSolver<double>& solv)
{
	std::cout << "solution:\n" << solv.solution() << std::endl;
}

#include <iostream>
#include <string>
#include <regex>
#include "matrix.hh"

bool read_matrix(num::Matrix<double> *mp);
void linear_algebra_mode();

int main(int argc, char *argv[])
{
	bool help = false, unkown = false;
	char c, mode;
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
			default:
				std::cerr << "unrecognized command line option -" << c << "." << std::endl;
				argc = 0;
				unkown = true;
				break;
			}
		}
	}

	if (unkown) {
		std::cout <<  "Try: '-h'\n";
		return 0;
	}

	if (help) {
		std::cout << "USAGE: numerical-analysis [option]\n\n"
			  << "OPTIONS:\n"
			  << "        -l: linear algebra module\n"
			  << "        -t: TODO"
			  << std::endl;

		return 0;
	}

	if (mode == 'l') {
		std::cout << "LINEAR ALGEBRA MODE" << std::endl;
		
		num::Matrix<double> *mat = new num::Matrix<double>;
		if (!read_matrix(mat)) {
			std::cout << "error reading matrix." << std::endl;
			return -1;
		}
		std::cout << *mat << std::endl;
		delete mat;
	} else if (mode == 't') {
		std::cout << "TEST MODE (dev only)" << std::endl;

		num::Matrix<double> m = num::create_identity_matrix<double>(3, 3);
		std::cout << m[0][0] << std::endl;
	}
	
	return 0;
}

bool read_matrix(num::Matrix<double> *mp)
{
	std::cout << "matrix dimensions:\n";
	unsigned rows = 0, cols = 0;
	std::cout << "rows: ";
	std::cin >> rows;
	std::cout << "cols: ";
	std::cin >> cols;

	*mp = num::Matrix<double>{ rows, cols };
	
	std::cout << "reading matrix (a00, a01[, ...];a10, a11[, ...][; ...]):\n";
	std::string str;
	std::cin >> str;
	
	std::regex row_regex{ ".+?;" };
	std::regex col_regex{ "[\\d.]+(?=,|;)" };

	std::sregex_iterator row_begin{ str.begin(), str.end(), row_regex };
	std::sregex_iterator row_end{ };
	
	unsigned row_count = 0;
	for (std::sregex_iterator row_it = row_begin; row_it != row_end; ++row_it) {
		if (row_count == rows) return false;

		std::string row = row_it->str();
		
		std::sregex_iterator col_begin{ row.begin(), row.end(), col_regex };

		unsigned col_count = 0;
		for (std::sregex_iterator col_it = col_begin; col_it != row_end; ++col_it) {
			if (col_count == cols) return false;

			(*mp)(row_count, col_count) = std::stod(col_it->str());

			col_count++;
		}

		row_count++;
	}
	
	return true;
}

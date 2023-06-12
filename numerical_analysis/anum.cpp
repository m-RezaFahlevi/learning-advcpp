#include <iostream>
#include <chrono>
#include <random>
#include "anum.h"

/* Set seed that will be used as a generator in
 * pseudo random number generator (PRNG) function
 */
const int seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 generator(seed);

/* runif stand for random uniform, return a number
 * randomly with uniform probability distribution
 * at range at_leas to at_most
 */
int runif(int at_least, int at_most) {
	std::uniform_int_distribution<int> randint(at_least, at_most);
	return randint(generator);
}

/* overloading runif */
double runif(double at_least, double at_most) {
	std::uniform_real_distribution<double> randu(at_least, at_most);
	return randu(generator);
}

LinearAlgebra::Matrix::Matrix(int nrows, int ncols) {
	nrow = nrows; ncol = ncols;
	mat = new double *[nrow];
	for (int row = 0; row < nrow; row++) {
		mat[row] = new double[ncol];
		for (int col = 0; col < ncol; col++) {
			mat[row][col] = row == col ? 1.0 : 0.0;
		}
	}
}

LinearAlgebra::Matrix::Matrix(std::vector<double> v, int nrows, int ncols) {
	std::vector<double>::iterator v_itr = v.begin();
	nrow = nrows; ncol = ncols;
	mat = new double *[nrow];
	int counter = 0;
	for (int row = 0; row < nrow; row++) {
		mat[row] = new double[ncol];
		for (int col = 0; col < ncol; col++) {
			mat[row][col] = *v_itr;
			v_itr++;
		}
	}
}

LinearAlgebra::Matrix::~Matrix() {
	for (int row = 0; row < nrow; row++)
		delete mat[row];
	delete mat;
}

void LinearAlgebra::Matrix::print() {
	for (int row = 0; row < nrow; row++) {
		for (int col = 0; col < ncol; col++)
			std::cout << mat[row][col] << " ";
		std::cout << std::endl;
	}
}

void LinearAlgebra::Matrix::println(std::string sentence) {
	std::cout << sentence << std::endl;
	for (int row = 0; row < nrow; row++) {
		for (int col = 0; col < ncol; col++)
			std::cout << mat[row][col] << " ";
		std::cout << std::endl;
	}
}

void LinearAlgebra::Matrix::forward_substitution(std::vector<double> b) {
	for (int pivot = 0; pivot < nrow; pivot++) {
		double scalar = 1 / mat[pivot][pivot];
		b.at(pivot) = scalar * b.at(pivot);
		for (int column = pivot; column < nrow; column++) {
			mat[pivot][column] = scalar * mat[pivot][column];
		}
		for (int row = pivot + 1; row < nrow; row++) {
			scalar = mat[row][pivot];
			for (int column = pivot; column < nrow; column++)
				mat[row][column] = mat[row][column] - scalar * mat[pivot][column];
			b.at(row) = b.at(row) - scalar * b.at(pivot);
		}
	}
}


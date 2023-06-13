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
	this->nrow = nrows;
	this->ncol = ncols;
	pseudo_mat = new double[nrow * ncol];
	for (int row = 0; row < nrow; row++) {
		for (int col = 0; col < ncol; col++) {
			int k = row * ncol + col;
			pseudo_mat[k] = row == col ? 1.0 : 0.0;
		}
	}
}

LinearAlgebra::Matrix::Matrix(std::vector<double> v, int nrows, int ncols) {
	std::vector<double>::iterator v_itr = v.begin();
	this->nrow = nrows;
	this->ncol = ncols;
	pseudo_mat = new double[nrow * ncol];
	for (int row = 0; row < nrow; row++) {
		for (int col = 0; col < ncol; col++) {
			int k = row * ncol + col;
			pseudo_mat[k] = *v_itr;
			v_itr++;
		}
	}
}

LinearAlgebra::Matrix::~Matrix() {
	delete[] pseudo_mat;
}

void LinearAlgebra::Matrix::print() {
	for (int row = 0; row < nrow; row++) {
		for (int col = 0; col < ncol; col++) {
			int k = row * ncol + col;
			std::cout << pseudo_mat[k] << " ";
		}
		std::cout << std::endl;
	}
}

void LinearAlgebra::Matrix::println(std::string sentence) {
	std::cout << sentence << std::endl;
	for (int row = 0; row < nrow; row++) {
		for (int col = 0; col < ncol; col++) {
			int k = row * ncol + col;
			std::cout << pseudo_mat[k] << " ";
		}
		std::cout << std::endl;
	}
}

void LinearAlgebra::Matrix::forward_substitution(std::vector<double> b) {
	for (int pivot = 0; pivot < nrow; pivot++) {
		int pivot_indice = pivot * ncol + pivot;
		double scalar = 1 / pseudo_mat[pivot_indice];
		b.at(pivot) = scalar * b.at(pivot);
		for (int column = pivot; column < nrow; column++) {
			int k = pivot * ncol + column;
			pseudo_mat[k] = scalar * pseudo_mat[k];
		}
		for (int row = pivot + 1; row < nrow; row++) {
			int scalar_indice = row * ncol + pivot;
			scalar = pseudo_mat[scalar_indice];
			for (int column = pivot; column < nrow; column++) {
				int matel_indice = row * ncol + column; // matrix element indice
				pseudo_mat[matel_indice] = pseudo_mat[matel_indice]  - scalar * pseudo_mat[pivot * ncol + column];
			}
			b.at(row) = b.at(row) - scalar * b.at(pivot);
		}
	}
}

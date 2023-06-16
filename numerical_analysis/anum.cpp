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

LinearAlgebra::Matrix::Matrix(unsigned int nrows, unsigned int ncols) {
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

LinearAlgebra::Matrix::Matrix(std::vector<double> v, unsigned int nrows, unsigned int ncols) {
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
	pseudo_mat = nullptr;
}


LinearAlgebra::Matrix &LinearAlgebra::Matrix::operator =(const Matrix &param) {
	this->nrow = param.nrow;
	this->ncol = param.ncol;
	this->pseudo_mat = param.pseudo_mat;
	return *this;
}

double LinearAlgebra::Matrix::operator [](const unsigned int k) {
	return pseudo_mat[k];
}

LinearAlgebra::Matrix LinearAlgebra::Matrix::operator +(const Matrix param) {
	std::vector<double> c_vec;
	int k = nrow * ncol;
	for (int k_itr = 0; k_itr < k; k_itr++)
		c_vec.push_back(pseudo_mat[k_itr] + param.pseudo_mat[k_itr]);
	LinearAlgebra::Matrix C(c_vec, nrow, ncol);
	return C;
}

LinearAlgebra::Matrix LinearAlgebra::Matrix::operator -(const Matrix param) {
	std::vector<double> c_vec;
	int k = nrow * ncol;
	for (int k_itr = 0; k_itr < k; k_itr++)
		c_vec.push_back(pseudo_mat[k_itr] - param.pseudo_mat[k_itr]);
	LinearAlgebra::Matrix C(c_vec, nrow, ncol);
	return C;
}

LinearAlgebra::Matrix LinearAlgebra::Matrix::operator *(const Matrix param) {
	std::vector<double> c_vec;
	for (int row = 0; row < nrow; row++) {
		for (int col = 0; col < ncol; col++) {
			double c_el = 0;
			for (int k = 0; k < nrow; k++) { // or k < param.ncol
				int pseudo_matel = row * ncol + k; // A[i, k] is an element from matrix A
				int param_matel = k * ncol + col; // B[k, j] is an element from matrix B
				c_el += pseudo_mat[pseudo_matel] * param.pseudo_mat[param_matel];
			}
			c_vec.push_back(c_el);
		}
	}
	LinearAlgebra::Matrix C(c_vec, nrow, param.ncol);
	return C;
}

LinearAlgebra::Matrix LinearAlgebra::Matrix::operator *(const double scalar) {
	int k = nrow * ncol;
	double *mat_ptr = pseudo_mat;
	for (int k_itr = 0; k_itr < k; k_itr++) {
		*mat_ptr *= scalar;
		mat_ptr++;
	}
	mat_ptr = nullptr;
	return *this;
}

int LinearAlgebra::Matrix::get_nrow() {
	return nrow;
}

int LinearAlgebra::Matrix::get_ncol() {
	return ncol;
}

double LinearAlgebra::Matrix::get_matel(const unsigned int i, const unsigned int j) {
	int indice = i * ncol + j;
	return pseudo_mat[indice];
}

void LinearAlgebra::Matrix::set_matel(const double val, const unsigned int i, const unsigned int j)
{
	int indice = i * ncol + j;
	pseudo_mat[indice] = val;
}

double LinearAlgebra::Matrix::at(const unsigned int i, const unsigned int j) {
	return pseudo_mat[i * ncol + j];
}

void LinearAlgebra::forward_substitution(Matrix A, std::vector<double> &b) {
	Matrix *A_ptr = &A;
	std::vector<double> *b_ptr = &b;
	int nrow = A_ptr->get_nrow();
	int ncol = A_ptr->get_ncol();
	for (int pivot = 0; pivot < nrow; pivot++) {
		double scalar = 1 / A_ptr->get_matel(pivot, pivot);
		b_ptr->at(pivot) *= scalar;
		for (int column = pivot; column < nrow; column++) {
			double updated_val = scalar * A_ptr->get_matel(pivot, column);
			A_ptr->set_matel(updated_val, pivot, column);
		}
		for (int row = pivot + 1; row < nrow; row++) {
			scalar = A_ptr->get_matel(row, pivot);
			for (int column = pivot; column < nrow; column++) {
				double updated_val = A_ptr->get_matel(row, column) - scalar * A_ptr->get_matel(pivot, column);
				A_ptr->set_matel(updated_val, row, column);
			}
			b_ptr->at(row) = b_ptr->at(row) - scalar * b_ptr->at(pivot);
		}
	}
	A_ptr = nullptr;
	b_ptr = nullptr;
}

void LinearAlgebra::back_substitution(Matrix U, std::vector<double> &y) {
	Matrix *U_ptr = &U;
	std::vector<double> *y_ptr = &y;
	int npivot = y_ptr->size();
	for (int pivot = npivot - 1; pivot >= 0; pivot--) {
		for (int row = pivot - 1; row >= 0; row--) {
			double updated_val = U_ptr->get_matel(row, pivot) - (U_ptr->get_matel(row, pivot) * U_ptr->get_matel(pivot, pivot));
			y_ptr->at(row) -= U_ptr->get_matel(row, pivot) * y_ptr->at(pivot);
			U_ptr->set_matel(updated_val, row, pivot);
		}
	}
	U_ptr = nullptr;
	y_ptr = nullptr;
}

void println(std::vector<double> v_vec) {
	for (double v_val: v_vec)
		std::cout << v_val << std::endl;
	std::cout << std::endl;
}

void println(std::vector<double> v_vec, std::string sentence) {
	std::cout << sentence << std::endl;
	for (double v_val: v_vec)
		std::cout << v_val << std::endl;
	std::cout << std::endl;
}

void println(LinearAlgebra::Matrix A) {
	int nrow = A.get_nrow();
	int ncol = A.get_ncol();
	for (int row = 0; row < nrow; row++) {
		for (int col = 0; col < ncol; col++) {
			int k = row * ncol + col;
			std::cout << A[k] << " ";
		}
		std::cout << std::endl;
	}
}

void println(LinearAlgebra::Matrix A, std::string sentence) {
	std::cout << sentence << std::endl;
	int nrow = A.get_nrow();
	int ncol = A.get_ncol();
	for (int row = 0; row < nrow; row++) {
		for(int col = 0; col < ncol; col++)
			std::cout << A.at(row, col) << " ";
		std::cout << std::endl;
	}
}


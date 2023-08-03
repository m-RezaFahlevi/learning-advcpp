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

/* Constructor Matrix return a m x n identity matrix, i.e.,
 * a matrix which its diagonal elements are one and the rest are zero.
 * There are two parameters, nrows determine the number of row of
 * a matrix and ncols determine the number of column of a matrix,
 * nrows and ncols are positive integer >= 1
 */
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

/* Constructor Matrix for given vector v where the number of elements
 * of v is m x n, return a m x n matrix where the elements are vector v.
 * There are two parameters, nrows determine the number of row of a matrix
 * and ncols determine the number of column of a matrix,
 * nrows and ncols are positive integer >= 1
 */
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

// Destructor of a Matrix
LinearAlgebra::Matrix::~Matrix() {
	pseudo_mat = nullptr;
}

// Assignment operator for a matrix
// if A, B are matrix, then assignment operator enable us
// to assign matrix B such that (for example) B = A * 2;
LinearAlgebra::Matrix &LinearAlgebra::Matrix::operator =(const Matrix &param) {
	this->nrow = param.nrow;
	this->ncol = param.ncol;
	this->pseudo_mat = param.pseudo_mat;
	return *this;
}

// Access element of pseudo matrix directly
double LinearAlgebra::Matrix::operator [](const unsigned int k) {
	return pseudo_mat[k];
}

// + : (R^(mxn),R^(mxn)) -> R^(mxn)
// Enable us to perform matrix additon, return a new matrix
LinearAlgebra::Matrix LinearAlgebra::Matrix::operator +(const Matrix param) {
	std::vector<double> c_vec;
	int k = nrow * ncol;
	for (int k_itr = 0; k_itr < k; k_itr++)
		c_vec.push_back(pseudo_mat[k_itr] + param.pseudo_mat[k_itr]);
	LinearAlgebra::Matrix C(c_vec, nrow, ncol);
	return C;
}

// - : (R^(mxn), R^(mxn)) -> R^(mxn)
// Enable us to perform matrix substraction, return a new matrix
LinearAlgebra::Matrix LinearAlgebra::Matrix::operator -(const Matrix param) {
	std::vector<double> c_vec;
	int k = nrow * ncol;
	for (int k_itr = 0; k_itr < k; k_itr++)
		c_vec.push_back(pseudo_mat[k_itr] - param.pseudo_mat[k_itr]);
	LinearAlgebra::Matrix C(c_vec, nrow, ncol);
	return C;
}

// * : (R^(mxn), R^(mxn)) -> R^(mxn)
// Enable us to perform matrix multiplication, return a new matrix
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

// * : (R^(mxn), R) -> R^(mxn)
// Enable us to scale a matrix with scalar, i.e., post multiply matrix by scalar
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

// Return the number of row of a matrix
int LinearAlgebra::Matrix::get_nrow() {
	return nrow;
}

// Return the number of column of a matrix
int LinearAlgebra::Matrix::get_ncol() {
	return ncol;
}

// Get element of a matrix at row i and column j
double LinearAlgebra::Matrix::get_matel(const unsigned int i, const unsigned int j) {
	int indice = i * ncol + j;
	return pseudo_mat[indice];
}

// Set element of a matrix at row i and column j by value val
void LinearAlgebra::Matrix::set_matel(const double val, const unsigned int i, const unsigned int j)
{
	int indice = i * ncol + j;
	pseudo_mat[indice] = val;
}

// Get element of a matrix at row i and column j
double LinearAlgebra::Matrix::at(const unsigned int i, const unsigned int j) {
	return pseudo_mat[i * ncol + j];
}

// Enable us to perform matrix transpose, return a new matrix
LinearAlgebra::Matrix LinearAlgebra::transpose(Matrix A) {
	Matrix *A_ptr = &A;
	Matrix A_tr(A_ptr->get_ncol(), A_ptr->get_nrow());
	int nrow = A_ptr->get_nrow();
	int ncol = A_ptr->get_ncol();
	for (int row = 0; row < nrow; row++) {
		for (int col = 0; col < ncol; col++) {
			double updated_val = A_ptr->get_matel(row, col);
			A_tr.set_matel(updated_val, col, row);
		}
	}
	return A_tr;
}

/* Perform forward_substitution to a matrix A, i.e.,
 * decompose matrix into its upper-triangular form
 */
void LinearAlgebra::forward_substitution(Matrix A) {
	Matrix *A_ptr = &A;
	int nrow = A_ptr->get_nrow();
	int ncol = A_ptr->get_ncol();
	for (int pivot = 0; pivot < nrow; pivot++) {
		double scalar = 1 / A_ptr->get_matel(pivot, pivot);
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
		}
	}
	A_ptr = nullptr;
}

/* Perform forward subtitution to a matrix in a linear equation
 * Ax = b, where A is a matrix, x and b are vector of the same dimentions,
 * decompose matrix A into its upper-triangular form, vector b also affected
 */
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

/* Performing back_substitution for given upper-triangular matrix after
 * performing forward_substitution, it will transform any upper-triangular
 * matrix into an identity matrix
 */
void LinearAlgebra::back_substitution(Matrix U) {
	Matrix *U_ptr = &U;
	int npivot = U_ptr->get_ncol() > U_ptr->get_nrow() ? U_ptr->get_nrow() : U_ptr->get_ncol();
	for (int pivot = npivot - 1; pivot >= 0; pivot--) {
		for (int row = pivot - 1; row >= 0; row--) {
			double updated_val = U_ptr->get_matel(row, pivot) - (U_ptr->get_matel(row, pivot) * U_ptr->get_matel(pivot, pivot));
			U_ptr->set_matel(updated_val, row, pivot);
		}
	}
	U_ptr = nullptr;
}

/* Performing back_substitution for upper-triangular matrix U in
 * a linear equation Uy = b where y and b are vector
 */
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

// still in debugging proccess...
void LinearAlgebra::solve(Matrix A) {
	Matrix *A_ptr = &A;
	int nrow = A_ptr->get_nrow();
	int ncol = A_ptr->get_ncol();
	Matrix *A_inv = new Matrix(nrow, ncol); // new identity matrix
	// compute the forward substitution
	for (int pivot = 0; pivot < nrow; pivot++) {
		double scalar = 1 / A_ptr->get_matel(pivot, pivot);
		for (int column = pivot; column < nrow; column++) {
			double updated_val = scalar * A_ptr->get_matel(pivot, column);
			double updated_inv = scalar * A_inv->get_matel(pivot, column);
			A_ptr->set_matel(updated_val, pivot, column);
			A_inv->set_matel(updated_inv, pivot, column);
		}
		for (int row = pivot + 1; row < nrow; row++) {
			scalar = A_ptr->get_matel(row, pivot);
			for (int column = pivot; column < nrow; column++) {
				double updated_val = A_ptr->get_matel(row, column) - scalar * A_ptr->get_matel(pivot, column);
				double updated_inv = A_inv->get_matel(row, column) - scalar * A_inv->get_matel(pivot, column);
				A_ptr->set_matel(updated_val, row, column);
				A_inv->set_matel(updated_inv, row, column);
			}
		}
	}
	// compute the back substitution
	for (int pivot = nrow- 1; pivot >= 0; pivot--) {
		for (int row = pivot - 1; row >= 0; row--) {
			double updated_val = A_ptr->get_matel(row, pivot) - (A_ptr->get_matel(row, pivot) * A_ptr->get_matel(pivot, pivot));
			double updated_inv = A_inv->get_matel(row, pivot) - (A_inv->get_matel(row, pivot) * A_ptr->get_matel(pivot, pivot));
			A_ptr->set_matel(updated_val, row, pivot);
			A_inv->set_matel(updated_inv, row, pivot);
		}
	}
	// update element of pseudo matrix
	for (int row = 0; row < nrow; row++) {
		for (int column = 0; column < ncol; column++) {
			double updated_inv = A_inv->get_matel(row, column);
			A_ptr->set_matel(updated_inv, row, column);
		}
	}
}

void LinearAlgebra::lu_factcomp(Matrix A) {
	LinearAlgebra::Matrix *A_ptr = &A;
	int N = A_ptr->get_nrow() * A_ptr->get_ncol();
	for (int pivot = 0; pivot < N-1; pivot++) {
		for (int row = pivot + 1; row < N - 1; row++) {
			double scalar = - A_ptr->get_matel(row, pivot) / A_ptr->get_matel(pivot, pivot);
			A_ptr->set_matel(scalar, row, pivot);
			for (int column = pivot + 1; column < N - 1; column++) {
				double updated_val = A_ptr->get_matel(row, column) + (scalar * A_ptr->get_matel(pivot, column));
				A_ptr->set_matel(updated_val, row, column);
			}
		}
	}
	A_ptr = nullptr;
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


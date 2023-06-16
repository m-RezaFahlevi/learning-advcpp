#include <iostream>
#include "anum.h"

int main(void) {
	std::vector<double> a = {3.0, 2.3, 3.5, 4.5, 8.3, 6.3, 7.2, 8.9, 9.3};
	std::vector<double> b_vec = {6.0, 7.0, 4.2};
	LinearAlgebra::Matrix A(a, 3, 3);
	println(A, "Matrix A:");
	println(b_vec, "row matrix b:");
	LinearAlgebra::forward_substitution(A, b_vec);
	println(A, "After forward substitution\nMatrix A:");
	println(b_vec, "row matrix b:");
	LinearAlgebra::back_substitution(A, b_vec);
	println(b_vec, "After back substitution\nrow matrix b:");
	println(A, "Matrix A:");
}

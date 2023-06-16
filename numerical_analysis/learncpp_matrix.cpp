#include <iostream>
#include "anum.h"

int main(void) {
	std::vector<double> a = {12.0, 2.2, 3.3, 4.4, 5.2, 6.1, 7.5, 8.5, 9.7};
	std::vector<double> b_vec = {5.3, 3.5, 4.6};
	LinearAlgebra::Matrix A(a, 3, 3);
	println(A, "Matrix A:");
	println(b_vec, "row matrix b:");
	LinearAlgebra::forward_substitution(A, b_vec);
	println(A, "After forward substitution\nMatrix A:");
	println(b_vec, "row matrix b:");
}

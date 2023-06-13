#include <iostream>
#include "anum.h"

int main(void) {
	std::vector<double> a = {1.0, 2.0, 3.2, 4.5, 4.2, 1.3, 4.5, 1.4, 9.9};
	std::vector<double> b = {3.2, 2.6, 7.7};
	std::vector<double> c = {1.0, 2.3, 3.2, 5.4, 3.2};
	LinearAlgebra::Matrix A(a, 3, 3);
	A.println("Matrix A:");
	A.forward_substitution(b);
	A.println("A after forward substitution:");

	LinearAlgebra::Matrix B(5, 5);
	B.forward_substitution(c);
	B.println("");
}

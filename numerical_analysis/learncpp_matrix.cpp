#include "anum.h"

int main(void) {
	std::vector<double> a = {1.1, 2.0, 3.2, 4.5, 4.2, 1.3, 4.5, 1.4, 9.9};
	std::vector<double> b = {3.2, 2.6, 7.7};
	LinearAlgebra::Matrix A(a, 3, 3); A.println("Matrix A:");
	A.forward_substitution(b);
	A.println("Matrix A after forward_substitution:");
	LinearAlgebra::Matrix B(4, 4);
	B.println("Matrix B:");
	B.forward_substitution(a);
	B.println("Matrix B after forward_substitution:");
}

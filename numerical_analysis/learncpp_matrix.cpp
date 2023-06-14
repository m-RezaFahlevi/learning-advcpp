#include <iostream>
#include "anum.h"

int main(void) {
	std::vector<double> a = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
	LinearAlgebra::Matrix A(a, 3, 3); A.println("Matrix A:");
	LinearAlgebra::Matrix B(3, 3); B.println("Matrix B:");
	LinearAlgebra::Matrix C = A - B; C.println("Matrix C:");
	std::cout << C.get_nrow() << " " << C.get_ncol() << std::endl;
	int *ptr;
	ptr = C.dim();
	std::cout << ptr[0] << " " << ptr[1] << "\n";
	std::cout << C.at(1, 1) << std::endl;
	delete[] ptr;
}

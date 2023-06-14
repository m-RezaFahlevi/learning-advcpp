#include <vector>
#include <string>

namespace LinearAlgebra {
	class Matrix {
		double *pseudo_mat;
		unsigned int nrow, ncol;
		public:
			Matrix(unsigned int, unsigned int); // constructor
			Matrix(std::vector<double> v, unsigned int, unsigned int); //constructor for given vector
			~Matrix();
			Matrix &operator =(const Matrix &param);
			double operator [](const unsigned int k);
			Matrix operator +(const Matrix param);
			Matrix operator -(const Matrix param);
			int get_nrow();
			int get_ncol();
			int *dim();
			double at(const unsigned int i, const unsigned int j); // used only in main fun
			void print();
			void println(std::string sentence);
			void forward_substitution(std::vector<double> b);
	};
}

#include <vector>
#include <string>

namespace LinearAlgebra {
	class Matrix {
		double *pseudo_mat;
		unsigned int nrow, ncol;
		public:
			Matrix(unsigned int, unsigned int); // constructor
			Matrix(std::vector<double> v, unsigned int, unsigned int); //constructor for given vector
			~Matrix(); // destructor
			Matrix &operator =(const Matrix &param);
			double operator [](const unsigned int k);
			Matrix operator +(const Matrix param);
			Matrix operator -(const Matrix param);
			Matrix operator *(const Matrix param);
			Matrix operator *(const double);
			int get_nrow();
			int get_ncol();
			double get_matel(const unsigned int, const unsigned int);
			void set_matel(const double val, const unsigned int, const unsigned int);
			double at(const unsigned int i, const unsigned int j); // used only in fun
	};
	void forward_substitution(Matrix, std::vector<double>&);
	void back_substitution(Matrix, std::vector<double>&);
}

void println(std::vector<double>);
void println(std::vector<double>, std::string);
void println(LinearAlgebra::Matrix);
void println(LinearAlgebra::Matrix, std::string);

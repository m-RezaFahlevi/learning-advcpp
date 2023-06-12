#include <vector>
#include <string>

namespace LinearAlgebra {
	class Matrix {
		int nrow, ncol;
		double **mat;
		public:
			Matrix(int, int);
			Matrix(std::vector<double> v, int, int);
			~Matrix();
			void print();
			void println(std::string sentence);
			void forward_substitution(std::vector<double> b);
	};
}

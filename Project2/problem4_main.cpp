#include <iostream>
#include "problem3_functions.hpp"
#include "problem4_functions.hpp"
#include "problem2_functions.hpp"

int main(){

	//b) Testing jacobi_rotate() with N=6 and ...
	const int N = 6;
	arma::mat A = set_up_A_matrix(N);
	arma::mat R = arma::eye(N, N);
	int k, l = 0;

	jacobi_rotate(A, R, k, l);

	std::cout << "A-matrix with eigenvalues along the diagonal" << std::endl;
	A.print();
	std::cout << "\n" << std::endl;
	std::cout << "R-matrix with eigenvectors as columns" << std::endl;
	R.print();
	std::cout << "\n" << std::endl;


	return 0;
}
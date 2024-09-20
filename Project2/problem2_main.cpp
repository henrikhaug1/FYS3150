#include <iostream>
#include <armadillo>
#include "problem2_functions.hpp"

int main(){

	int N = 6;

	arma::mat analytical_eigvec(N, N);
	arma::vec analytical_eigval(N);

	analytical_eig_vec_val(analytical_eigvec, analytical_eigval, N);

	//checks correspondence between analytical and numerical solution
	test_eigval_eigvec(analytical_eigval, analytical_eigvec, N);

	return 0;
}
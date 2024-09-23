#include <iostream>
#include <armadillo>
#include "problem2_functions.hpp"

int main(){

	/* checks that the eigenvalues and eigenvectors from Armadillo agrees 
	with the analytical result for N=6*/
	test_eigval_eigvec();

	return 0;
}
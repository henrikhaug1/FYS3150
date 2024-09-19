#include <iostream>
#include <armadillo>
#include "problem2_functions.hpp"
#include "problem3_functions.hpp"
#include "problem4_functions.hpp"
#include "problem5_functions.hpp"

int main(){

	double eps = 1.0e-8;
	arma::vec eigenvalues;
	arma::mat eigenvectors;
	const int maxiter = 100;
	int iterations;
	bool converged;
	arma::vec N = {5};

	for(int i = 0; i < N.size(); ++i){
		const arma::mat A = set_up_A_matrix(N[i]);
		jacobi_eigensolver(A, eps, eigenvalues, eigenvectors, maxiter, iterations, converged);
	}

	
	return 0;
}
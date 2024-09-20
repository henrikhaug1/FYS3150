#include <iostream>
#include <armadillo>
#include "problem2_functions.hpp"
#include "problem3_functions.hpp"
#include "problem4_functions.hpp"
#include "problem5_functions.hpp"

int main(){

	//a)
	double eps = 1.0e-8;
	arma::vec eigenvalues;
	arma::mat eigenvectors;
	const int maxiter = 100;
	int iterations;
	bool converged;
	arma::vec N = {5, 6, 7, 8, 9};

	for(int i = 0; i < N.size(); ++i){
		arma::mat A = set_up_A_matrix(N[i]);
		jacobi_eigensolver(A, eps, eigenvalues, eigenvectors, maxiter, iterations, converged);
	}


	//b)
	// Generate random N*N matrix
	arma::mat A_dense = arma::randu<arma::mat>(5, 5);

	// Symmetrize the matrix by reflecting the upper triangle to lower triangle
	A_dense = arma::symmatu(A_dense); 

	jacobi_eigensolver(A_dense, eps, eigenvalues, eigenvectors, maxiter, iterations, converged);

	return 0;
}
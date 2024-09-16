#include <iostream>
#include <armadillo>
#include "problem2_functions.hpp"
#include "problem3_functions.hpp"
#include "problem4_functions.hpp"
#include "problem5_functions.hpp"

int main(){

	arma::mat A;
	double eps = 1.0e-8;
	arma::vec eigenvalues;
	arma::mat eigenvectors;
	int maxiter = 100;
	int iterations;
	bool converged;
	jacobi_eigensolver(A, eps, eigenvalues, eigenvectors, maxiter, iterations, converged);

	return 0;
}
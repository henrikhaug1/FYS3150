#include <iostream>
#include "problem3_functions.hpp"
#include "problem4_functions.hpp"

int main(){
	arma::mat A = set_up_A_matrix(N); //Seting up the tridiagonal matrix
	arma::vec eigval = solve_eigval(A)
	arma::mat eigvec = solve_eigvec(A)
	jacobi_eigensolver(A, 1e-10, eigval, eigvec) // add rest of the arguments
	return 0;
}
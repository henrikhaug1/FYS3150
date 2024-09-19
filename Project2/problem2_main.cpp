#include <iostream>
#include "problem2_functions.hpp"

int main(){

	//Setting up tridiagonal A for N = 6
	arma::mat A = set_up_A_matrix(6);

	//Solving matrix equation 
	arma::vec eigval = solve_eigval(A);
	arma::mat eigvec = solve_eigvec(A);

	//checks correspondence between analytical and numerical solution
	test_eigval_eigvec(eigval, eigvec);

	return 0;
}
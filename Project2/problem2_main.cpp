#include <iostream>
#include "problem2_functions.hpp"

int main(){
	arma::mat A = set_up_A_matrix(6);
	solve_mat_eq(A);

	return 0;
}
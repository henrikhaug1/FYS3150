#ifndef __problem2_functions_hpp__
#define __problem2_functions_hpp__

#include <iostream>
#include <string>
#include <armadillo>

arma::mat set_up_A_matrix(const int N);

arma::vec solve_eigval(arma::mat A);

arma::mat solve_eigvec(arma::mat A);

void test_eigval_eigvec(arma::vec eigval, arma::mat eigvec);

#endif

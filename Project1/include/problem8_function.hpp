#ifndef __problem8_functions_hpp__
#define __problem8_functions_hpp__

#include <armadillo>
#include <iostream>

arma::vec absolute_error(arma::vec approx_vec, arma::vec true_vec);

arma::vec relative_error(arma::vec approx_vec, arma::vec true_vec);

#endif
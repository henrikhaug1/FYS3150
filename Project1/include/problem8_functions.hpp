#ifndef __problem8_functions_hpp__
#define __problem8_functions_hpp__

#include <armadillo>
#include <string>
#include <iostream>

arma::vec absolute_error(arma::vec approx_vec, arma::vec true_vec);

arma::vec relative_error(arma::vec approx_vec, arma::vec true_vec);

// function that writes error values to file
void write_error_to_file(std::string filename, arma::vec error_vec);


#endif
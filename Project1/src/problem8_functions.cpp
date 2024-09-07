#include <iosstream>
#include "problem8_functions.hpp"

arma::vec absolute_error(arma::vec approx_vec, arma::vec true_vec){

	std::size_t length_vec = approx_vec.size();

	arma::vec absolute_error = arma::vec(length_vec);
	for(int i = 0; i < length_vec; i++){
		absolute_error[i] = std::abs(approx_vec[i] - true_vec[i]);
	}

	return absolute_error_vec;
}

arma::vec relative_error(arma::vec approx_vec, arma::vec true_vec){

	std::size_t length_vec = approx_vec.size();

	arma::vec relative_error = arma::vec(length_vec);
	for(int i = 0; i < length_vec; i++){
		relative_error[i] = std::abs((approx_vec[i] - true_vec[i]) / true_vec);
	}

	return relative_error_vec;
}





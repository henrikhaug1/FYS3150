#include "problem8_functions.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>



arma::vec absolute_error(arma::vec approx_vec, arma::vec true_vec){

	std::size_t length_vec = approx_vec.size();

	arma::vec absolute_error_vec = arma::vec(length_vec);
	for(int i = 0; i < length_vec; i++){
		double abs_value = fabs(approx_vec[i] - true_vec[i]);
		absolute_error_vec[i] = fabs(abs_value);
	}

	return absolute_error_vec;
}

arma::vec relative_error(arma::vec approx_vec, arma::vec true_vec){

	std::size_t length_vec = approx_vec.size();

	arma::vec relative_error_vec = arma::vec(length_vec);
	for(int i = 0; i < length_vec; i++){
		double rel_value = (approx_vec[i] - true_vec[i]) / true_vec[i];
		relative_error_vec[i - 1] = fabs(rel_value);
	}

	return relative_error_vec;
}

arma::vec make_plotting_vec(std::string type_error, arma::vec n_step){


	// Function is taking vector; n_step = {10, 100, 1000}
	//Read from files in loop 
	std::size_t how_many_graphs = n_step.size();
	for(int i = 0; i < how_many_graphs; i++){

		int n = how_many_graphs[i];
		std::fstream infile;

		std::string filename = type_error + std::to_string(n) + ".txt";
		infile.open(filename);

    	ofile << std::scientific << std::setprecision(5);
    	ofile << error_vec;


	}
}





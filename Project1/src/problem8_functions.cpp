#include "problem8_functions.hpp"
#include "problem7_functions.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>
#include <armadillo>

double u(double x){
	//std::cout << 2.0;//(1 - ((1 - std::exp(-10)) * x) - std::exp((-10) * x));

  return (1 - ((1 - std::exp(-10)) * x) - std::exp((-10) * x));
}

/*
//Calculating approximated second derivative aourond a given point x
double calc_approx(double x, double h){

	double approx = (u(x + h) - 2 * u(x) + u(x - h)) / (h * h);
	return approx;
}

*/


void write_x_v_u(int n_step){

	arma::mat v_x_mat = thomas_algo(n_step, -1, 2, -1);
	arma::vec v_vec = v_x_mat.col(0);
	arma::vec x_vec = v_x_mat.col(1);

	arma::vec exact_vec = arma::vec(n_step);

	for(int i = 0.0; i < n_step; ++i){
		exact_vec[i] = u(static_cast<double>(i) / n_step);
	}


	std::ofstream ofile;
	std::string filename = "x_v_u" + std::to_string(n_step) + ".txt";
	ofile.open(filename);
	ofile << std::scientific << std::setprecision(8);
	ofile << "x                      v                  u" << "\n"; //making header for file

	for(int i = 1; i < n_step - 1; ++i){ 
		ofile << x_vec[i] << "     " << v_vec[i] << "     " << exact_vec[i] << "\n";

	}

	ofile.close();
}




#include "problem8_functions.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>
#include <armadillo>

double u(double x){

  return 100*exp(-10*x);
}

//Calculating approximated second derivative aourond a given point x
double calc_approx(double x, double h){

	double approx = (u(x+h) - 2*u(x) + u(x-h)) / (h*h);
	return approx;
}

//Calculating the exact souluton of u(x) around a given point x
double calc_exact(double x){

	double exact = 100 * exp(-10 * x);
	return exact;

}

//Calculating the absolute error around a given point x
double absolute_error(double approx, double exact){

	double absolute_err = fabs(approx - exact);
	return absolute_err;

}

//Calculating the relative error around a given point x
double relative_error(double approx, double exact){

	double relative_err = fabs((approx - exact) / exact);
	return relative_err;
}

//Writing h-, absolute error and relative error values to file 
void write_h_absolute_relative(arma::ivec n_step_vec, double h_min, double h_max, double x){

	int n = n_step_vec.size(); // {10, 100, 100} n=3

	for(int i = 0; i < n; i++){

		arma::vec h_vec = arma::linspace(h_min, h_max, n_step_vec[i]);
		arma::vec absolute_vec = arma::vec(n_step_vec[i]);
		arma::vec relative_vec = arma::vec(n_step_vec[i]);

		double exact = calc_exact(x);

		for(int j = 0; j < n_step_vec[i]; j++){ //i<10

			double approx = calc_approx(x, h_vec[j]);

			absolute_vec[j] = absolute_error(approx, exact);
			relative_vec[j] = relative_error(approx, exact);

		}

		std::ofstream ofile;
		std::string filename = "h-abs-rel" + std::to_string(n_step_vec[i]) + ".txt";
		ofile.open(filename);
		ofile << std::scientific << std::setprecision(5);
		ofile << "h               absolute error  relative error" << "\n"; //making header for file


		for(int k = 0; k < n_step_vec[i]; k++){ 
			ofile << h_vec[k] << "     " << absolute_vec[k] << "     " << relative_vec[k] << "\n";

		}


		ofile.close();

	}
}



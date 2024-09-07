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
void write_h_absolute_relative(int n_step, double h_min, double h_max, double x){

	arma::vec h_vec = arma::linspace(h_min, h_max, n_step);
	arma::vec absolute_vec = arma::vec(n_step);
	arma::vec relative_vec = arma::vec(n_step);

	double exact = calc_exact(x);

	for(int i = 0; i < n_step; i++){

		double approx = calc_approx(x, h_vec[i]);

		absolute_vec[i] = absolute_error(approx, exact);
		relative_vec[i] = relative_error(approx, exact);
	}

	std::ofstream ofile;
	ofile.open("h-abs-rel.txt");
	ofile << std::scientific << std::setprecision(5);
	ofile << "h               absolute error  relative error" << "\n";
	for(int i = 0; i < n_step ; i++){
		ofile << h_vec[i] << "     " << absolute_vec[i] << "     " << relative_vec[i] << "\n";
	}

	ofile.close();

}



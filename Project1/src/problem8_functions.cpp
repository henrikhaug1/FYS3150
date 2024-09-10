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

	double approx = (u(x + h) - 2 * u(x) + u(x - h)) / (h * h);
	return approx;
}

//Calculating the exact souluton of u(x) around a given point x
double calc_exact(double x){

	double exact = 10000 * exp(-10 * x);
	return exact;

}

//Writing h-, absolute error and relative error values to file 
void write_h_approx_exact(int n_step, double h_min, double h_max, double x){

	int width = 18;
	int prec = 10;

	double exact = calc_exact(x);

	//Calculate stepsize factor to generate .txt files with different n_step size
	double factor = pow(10, log10(1.0 / h_min) / (n_step - 1)); // factor to increase h n_step times from h_min to 1

	std::ofstream ofile;
	std::string filename = "h-approx-exact" + std::to_string(n_step) + ".txt";
	ofile.open(filename);
	ofile << std::scientific << std::setprecision(5);
	ofile << "h               aprrox val      exact val" << "\n"; //making header for file

	double h = h_min;
	for(int i = 0; i < n_step; i++){ 

		double approx = calc_approx(x, h);
		ofile << h << "     " << approx << "     " << exact << "\n";

		h *= factor;
	}

	ofile.close();
}









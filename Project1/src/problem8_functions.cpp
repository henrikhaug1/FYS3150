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
void write_h_approx_exact(arma::ivec n_step_vec, double h_min, double h_max, double x){

	int n = n_step_vec.size(); // {10, 100, 100} n=3

	for(int i = 0; i < n; i++){

			int steps = n_step_vec[i];

			arma::vec h = arma::linspace(h_min, h_max, steps);
			arma::vec approx = arma::vec(steps);

			double exact = calc_exact(x);

			for(int j = 0;j < steps; j++){
				approx[j] = calc_approx(x, h[j]);
			}

			std::ofstream ofile;
			std::string filename = "h-approx-exact" + std::to_string(n_step_vec[i]) + ".txt";
			ofile.open(filename);
			ofile << std::scientific << std::setprecision(5);
			ofile << "h               aprrox val  exact val" << "\n"; //making header for file


			for(int k = 0; k < steps; k++){ 
				ofile << h[k] << "     " << approx[k] << "     " << exact << "\n";

			}


		ofile.close();

	}
}

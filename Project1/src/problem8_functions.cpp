#include "problem8_functions.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>

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

//Writing h-, approx- and exact values to file 
void write_info_to_file(){

	
}



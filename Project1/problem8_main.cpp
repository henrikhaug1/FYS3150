#include "problem8_functions.hpp"
#include <iomanip>



int main(){

	int n_step = 1000; 
	double h_min = 1.0e-8;
	double h_max = 1.0;
	double x = 2.0;

	write_h_absolute_relative(n_step, h_min, h_max, x);

	return 0;

}
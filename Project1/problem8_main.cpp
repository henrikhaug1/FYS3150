#include "problem8_functions.hpp"
#include <iomanip>
#include <armadillo>



int main(){

	double h_min = 1.0e-8;
	double h_max = 1.0;
	double x = 0.5;

	write_h_approx_exact(10, h_min, h_max, x); //writing .txt file h-approx-exact10.txt
	write_h_approx_exact(100, h_min, h_max, x); //writing .txt file h-approx-exact100.txt
	write_h_approx_exact(1000, h_min, h_max, x); //writing .txt file h-approx-exact100.txt

	return 0;

}
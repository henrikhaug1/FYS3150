#ifndef __problem8_functions_hpp__
#define __problem8_functions_hpp__

#include <string>
#include <iostream>
#include <armadillo>

double u(double x);

double calc_approx(double x, double h);

double calc_exact(double x);

void write_h_approx_exact(int n_step, double h_min, double h_max, double x);

#endif
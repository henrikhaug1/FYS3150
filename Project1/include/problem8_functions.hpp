#ifndef __problem8_functions_hpp__
#define __problem8_functions_hpp__

#include <string>
#include <iostream>

double u(double x);

double calc_approx(double x, double h);

double calc_exact(double x);

double absolute_error(double approx, double exact);

double relative_error(double approx, double exact);

void write_h_approx_exact(int n_step, double h_min, double h_max, double approx, double exact);

#endif
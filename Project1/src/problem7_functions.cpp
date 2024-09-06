#include <iostream>
#include <vector>
#include <cmath>
#include <armadillo>
#include <iomanip>
#include "problem7_functions.cpp"

void thomas_algo(int n_step){

double h = 1.0/n_step;

arma::vec x = arma::linspace<arma::vec>(0, 1, n_step);
arma::vec f = 100 * exp(-10 * x);


arma::vec a = arma::vec(n_step - 1).fill(-1.);
arma::vec b = arma::vec(n_step).fill(2.);
arma::vec c = arma::vec(n_step - 1).fill(-1.);
arma::vec g = arma::vec(n_step);
arma::vec v = arma::vec(n_step).fill(0.);

arma::vec b_tilde = arma::vec(n_step - 1).fill(0);
arma::vec g_tilde = arma::vec(n_step - 1).fill(0);



for(int i = 0; i < n_step ; i++){
	g[i] = std::pow(h, 2) * f[i];
}





}

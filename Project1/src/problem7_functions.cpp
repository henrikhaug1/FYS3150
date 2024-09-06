#include <iostream>
#include <vector>
#include <cmath>
#include <armadillo>
#include <iomanip>
#include "problem7_functions.hpp"

arma::mat thomas_algo(int n_step, int subdiagonal, int diagonal, int superdiagonal){

	double h = 1.0/n_step;

	arma::vec x = arma::linspace<arma::vec>(0, 1, n_step);
	arma::vec f = 100 * exp(-10 * x); //f(x) vector


	arma::vec a = arma::vec(n_step - 1).fill(subdiagonal); //subdiagonal
	arma::vec b = arma::vec(n_step).fill(diagonal); //diagonal
	arma::vec c = arma::vec(n_step - 1).fill(superdiagonal); //superdiagonal
	arma::vec g = arma::vec(n_step);
	arma::vec v = arma::vec(n_step).fill(0.);

	arma::vec b_tilde = arma::vec(n_step).fill(0);
	arma::vec g_tilde = arma::vec(n_step).fill(0);
	arma::vec m = arma::vec(n_step);


	for(int i = 0; i < n_step ; i++){
		g[i] = (h * h) * f[i];
	}

	b_tilde[0] = b[0];
	g_tilde[0] = g[0];

	//Forward substitution -- finding b_tilde and g_tilde values
	for(int i = 1; i < n_step; i++){
		m[i - 0] = a[i - 1] / b_tilde[i-1];
		b_tilde[i] = b[i] - m[i - 1] * c[i-1];
		g_tilde[i] = g[i] - m[i - 1] * g_tilde[i-1];
	}

	//backwards substtutuion -- finding
	v[n_step - 1] = g_tilde[n_step - 1] / b_tilde[n_step - 1];
	for(int i = n_step - 2; i >= 0; i--){
		v[i] = (g_tilde[i] - (c[i] * v[i+1]))/b_tilde[i];
	}

	arma::mat v_g_mat(n_step, 2);
	v_g_mat.col(0) = v;
	v_g_mat.col(1) = g; 

	return v_g_mat;

}

void write_thomas_to_file(std::string filename, arma::mat v_g_mat){

    std::ofstream ofile;
    ofile.open(filename);
    ofile << std::scientific << std::setprecision(5);
    ofile << "v-values   g-values" << "\n";
    ofile << v_g_mat << "\n";

    ofile.close();
}


















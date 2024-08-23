#include <iostream>
#include <vector>
#include <cmath>
#include <armadillo>
#include <iomanip>




double u(double x) {
	double func = (1 - ((1 - exp(-10)) * x) - exp(-10 * x));
	return func;
	}

arma::vec fill_x_vec(int start, int stop, int n){
	arma::vec x_vec = arma::linspace<arma::vec>(start, stop, n);
	return x_vec;
}

arma::vec fill_ux_vec(arma::vec x_vec){	
	arma::vec ux_vec(x_vec.size());
	for(int i = 0; i < x_vec.size(); i++){
	        ux_vec(i) = u(x_vec(i));
	    }

	return ux_vec;
}

void write_to_file(std::string filename, arma::vec x_vec, arma::vec ux_vec) {
    std::ofstream ofile;
    ofile.open(filename);
    ofile << std::scientific << std::setprecision(5);
    ofile << "x values   u(x) values" << "\n";
    for (int i = 0; i < x_vec.size(); i++){
        ofile << x_vec[i] << " " << ux_vec[i] << "\n";
    }
    ofile.close();
}

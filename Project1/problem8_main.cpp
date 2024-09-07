#include "problem2_functions.hpp"
#include "problem7_functions.hpp"
#include "problem8_functions.hpp"

int main(){

	std::vector<int> n_step = {10, 100, 1000};
	for(int i = 0; i < n_step.size(); i++){
		int n = n_step[i];
		// extraction information from matrix
		arma::mat v_x_mat = thomas_algo(n, -1, 2, -1);
		arma::vec approx_vec = v_x_mat.col(0);
		arma::vec true_vec = fill_ux_vec(fill_x_vec(0, 1, n));

		// finding absolute- and relative error
		arma::vec abs = absolute_error(approx_vec, true_vec);
		arma::vec rel = relative_error(approx_vec, true_vec);
		std::string filename_abs = "absolute_error" + std::to_string(n) + ".txt";
		std::string filename_rel = "relative_error" + std::to_string(n) + ".txt";
		//writing absolute- and relative error values to file 
    	write_error_to_file(filename_abs, abs);
    	write_error_to_file(filename_rel, rel);
    }
	return 0;
}
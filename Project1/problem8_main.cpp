#include "problem2_functions.hpp"
#include "problem7_functions.hpp"
#include "problem8_functions.hpp"

int main(){

	// finding abolsute- and relative error for n_step = 10
	arma::mat v_x_mat_10 = thomas_algo(10, -1, 2, -1);
	arma::vec approx_vec_10 = v_x_mat_10.col(0);
	arma::vec true_vec_10 = fill_ux_vec(fill_x_vec(0, 1, 10));

	arma::vec abs_10 = absolute_error(approx_vec_10, true_vec_10);
	arma::vec rel_10 = relative_error(approx_vec_10, true_vec_10);

	// finding abolsute- and relative error for n_step = 100
	arma::mat v_x_mat_100 = thomas_algo(100, -1, 2, -1);
	arma::vec approx_vec_100 = v_x_mat_10.col(0);
	arma::vec true_vec_100 = fill_ux_vec(fill_x_vec(0, 1, 100));

	arma::vec abs_100 = absolute_error(approx_vec_100, true_vec_100);
	arma::vec rel_100 = relative_error(approx_vec_100, true_vec_100);

	// finding abolsute- and relative error for n_step = 1000
	arma::mat v_x_mat_1000 = thomas_algo(1000, -1, 2, -1);
	arma::vec approx_vec_1000 = v_x_mat_10.col(0);
	arma::vec true_vec_1000 = fill_ux_vec(fill_x_vec(0, 1, 1000));

	arma::vec abs_1000 = absolute_error(approx_vec_1000, true_vec_1000);
	arma::vec rel_1000 = relative_error(approx_vec_1000, true_vec_1000);


	return 0;
}
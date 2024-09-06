#include <iostream>
#include <tuple>
#include "problem7_functions.hpp"

int main(){

    arma::mat v_x_mat_10 = thomas_algo(10, -1, 2, -1);
    write_thomas_to_file("problem7_v_x_10steps.txt", v_x_mat_10);

    arma::mat v_x_mat_100 = thomas_algo(100, -1, 2, -1);
    write_thomas_to_file("problem7_v_x_100steps.txt", v_x_mat_100);

    arma::mat v_x_mat_1000 = thomas_algo(1000, -1, 2, -1);
    write_thomas_to_file("problem7_v_x_1000steps.txt", v_x_mat_1000);

    return 0;
}

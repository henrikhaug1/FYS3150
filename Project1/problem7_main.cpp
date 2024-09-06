#include <iostream>
#include <tuple>
#include "problem7_functions.hpp"

int main(){

    arma::mat v_g_mat = thomas_algo(10, -1, 2, -1);
    write_thomas_to_file("problem7_v_g", v_g_mat);

    return 0;
}

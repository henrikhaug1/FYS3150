#include "PDEModel.hpp"

#include <iostream>
#include <armadillo>

int main()
{

    // int argc, char* argv[]

	// if(argc != 11){
    //     std::cout << "Provide arguments: h, Δt, T, x_c, 𝛔_x, p_x, y_c, 𝛔_y, p_y and v0 "<< std::endl;
    //     return 1;
    // }

    // double h = atoi(argv[1]);
    // double dt = atoi(argv[2]);
    // double T = atoi(argv[3]);
    // double x_c = atoi(argv[4]);
    // double sigma_x = atoi(argv[5]);
    // double p_x = atoi(argv[6]);
    // double y_c = atoi(argv[7]);
    // double sigma_y = atoi(argv[8]);
    // double p_y = atoi(argv[9]);
    // double v0 = atoi(argv[10]);



    arma::cx_vec a = arma::cx_vec({1, 2, 3, 4, 5, 6, 7, 8, 9});//, 10, 11, 12, 13, 14, 15, 16});
    arma::cx_vec b = arma::cx_vec({1, 2, 3, 4, 5, 6, 7, 8, 9});//, 10, 11, 12, 13, 14, 15, 16});
    int M = 5;
    arma::cx_double r(2.0, 0);
    double dt = 0.1;
    double dx = 0.1;
    double dy = 0.1;
    double x_c = 0.25;
    double y_c = 0.5;
    double p_x = 200;
    double p_y = 0;
    double sigma_x = 0.05;
    double sigma_y = 0.05;

    PDEModel model(dt, dx, dy, x_c, y_c, sigma_x, sigma_y, p_x, p_y);
    std::vector u = model.initial_state(M);
    model.normalised_initial_state(u);

    auto result = model.construct_A_B(r, M, a, b);

    // Plotting code to see structure of A or B matrix
    // arma::sp_cx_mat A = std::get<0>(result);
    // arma::sp_cx_mat B = std::get<1>(result);
    // std::cout << 'Shape of Matrices A and B' << std::endl;
    // model.print_sp_matrix_structure(A);
    // model.print_sp_matrix_structure(B);

	return 0;
}
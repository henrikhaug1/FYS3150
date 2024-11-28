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



    arma::vec a = arma::vec({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
    arma::vec b = arma::vec({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
    int M = 6;
    double r = 2.;
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
    model.construct_A_B(a, b, r, M);




	return 0;
}
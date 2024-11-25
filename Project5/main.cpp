#include "PDEModel.hpp"

#include <iostream>
#include <armadillo>

int main(int argc, char* argv[])
{

	if(argc != 11){
        std::cout << "Provide arguments: h, Δt, T, x_c, 𝛔_x, p_x, y_c, 𝛔_y, p_y and v0 "<< std::endl;
        return 1;
    }

    double h = atoi(argv[1]);
    double dt = atoi(argv[2]);
    double T = atoi(argv[3]);
    double x_c = atoi(argv[4]);
    double sigma_x = atoi(argv[5]);
    double p_x = atoi(argv[6]);
    double y_c = atoi(argv[7]);
    double sigma_y = atoi(argv[8]);
    double p_y = atoi(argv[9]);
    double v0 = atoi(argv[10]);





	return 0;
}
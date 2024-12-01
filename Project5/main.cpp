#include "PDEModel.hpp"

#include <iostream>
#include <armadillo>


void save_matrix_to_csv(const arma::mat& matrix, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        // Iterate through the matrix and write values to file
        for (size_t i = 0; i < matrix.n_rows; ++i) {
            for (size_t j = 0; j < matrix.n_cols; ++j) {
                file << matrix(i, j);
                if (j < matrix.n_cols - 1) {
                    file << ","; // Add comma separator for CSV format
                }
            }
            file << "\n"; // New line at the end of each row
        }
        file.close();
    } else {
        std::cerr << "Error opening file " << filename << std::endl;
    }
}

int main()
{
    int M = 1000;
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

    arma::mat V(M-2, M-2, arma::fill::zeros);
    double v_0 = 1000000;
    int nr_slits = 1;
    double thickness = 0.02;
    double centre = 0.5;
    double middle_wall = 0.05;
    double opening = 0.05;
    model.construct_potential(V, v_0, M, nr_slits, thickness, centre, middle_wall, opening);
    auto result = model.construct_A_B(M, dx, dt, V);

    save_matrix_to_csv(V, "matrix.csv");

    //Plotting code to see structure of A or B matrix
    // arma::sp_cx_mat A = std::get<0>(result);
    // arma::sp_cx_mat B = std::get<1>(result);
    // std::cout << "Shape of Matrices A and B" << std::endl;
    // model.print_sp_matrix_structure(A);
    // model.print_sp_matrix_structure(B);

	return 0;
}